/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uusi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/30 15:58:58 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#define PI 3.14159265359
#define	PI2 PI / 2
#define PI3 3 * PI / 2
#define	DEGREE 0.1875
#define P_PLANE_W 320
#define P_PLANE_H 200
#define P_PLANE_MID_W 160
#define P_PLANE_MID_H 100
#define DIST_TO_P_PLANE 277
#define	MAX_VIEW_DISTANCE 1000
#define	FOV	60
#define EAST 0
#define NORTH 90
#define WEST 180
#define SOUTH 270
#define BLOCK 64

typedef struct s_rayinfo
{
	mlx_image_t *player;
	mlx_image_t *screen;
	double	angle;
	double	ray_angle;
	double	playerdir_x;
	double	playerdir_y;
	double	distance_h;
	double	distance_v;
}			t_rayinfo;

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int get_r(int rgba)
{
    // Move 3 bytes to the right and mask out the first byte.
    return ((rgba >> 24) & 0xFF);
}

double	ray_length(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	draw_line(int x_start, int y_start, int x_end, int y_end, mlx_image_t *screen)
{
	int	dx;
	int	dy;
	int	slope_x;
	int	slope_y;
	int	y;
	int	x;
	int xe;
	int	ye;

	printf("x_start: %d\n", x_start);
	printf("y_start: %d\n", y_start);
	printf("x_end: %d\n", x_end);
	printf("y_end: %d\n", y_end);
	ye = 0;
	xe = 0;
	y = 0;
	x = 0;
	x_start += 4;
	dx = x_end - x_start;	
	dy = y_end - y_start;
	slope_x = (2 * dy) - dx;
	slope_y = (2 * dx) - dy;
	if (dy <= dx)
	{
		if (dx >= 0)
		{
			x = x_start;
			y = y_start;
			xe = x_end;
		}
		else
		{
			x = x_end;
			y = y_end;
			xe = x_start;
		}
		mlx_put_pixel(screen, x, y, 155);
		while (x < xe)
		{
			x++;
			if (slope_x < 0)
				slope_x = slope_x + 2 * dy;
			else
			{
				if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0))
					y++;
				else
					y--;
				slope_x = slope_x + 2 * (dy - dx);
			}
			mlx_put_pixel(screen, x, y, 155);
		}	
	}
	else
	{
		if (dy >= 0)
		{
			x = x_start;
			y = y_start;
			ye = y_end;
		}
		else
		{
			x = x_end;
			y = y_end;
			ye = y_start;
		}
		mlx_put_pixel(screen, x, y, 155);
		while (y < ye)
		{
			y++;
			if (slope_y <= 0)
				slope_y = slope_y + 2 * dx;
			else
				x--;
			slope_y = slope_y + 2 * (dx - dy);
			mlx_put_pixel(screen, x, y, 155);
		}
	}
}

void	check_horizontal_hit(int p_x, int p_y, double step_x, double step_y, t_rayinfo *info)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	ray_y;
	double	ray_x;
	int		map_y;
	int		map_x;
	int		hit;
	
	hit = 0;
	if (info->ray_angle < WEST)
	{
		ray_y = floor(p_y / 64) * 64 + 64;
		printf("ray_y %f\n", ray_y);
		step_y = 64;
		step_x = 64 / floor(tan(info->ray_angle * PI / 180));
		printf("step_x %f\n", step_x);
	}
	if (info->ray_angle > WEST)
	{
		ray_y = floor(p_y / 64) * 64 - 1;
		printf("ray_y %f\n", ray_y);
		step_y = -64;
		step_x = 64 / floor(tan(info->ray_angle * PI / 180));
		printf("step_x %f\n", step_x);
	}
	ray_x = p_x + (p_y - (int)ray_y) / tan(info->ray_angle * PI / 180);
	printf("ray_x %f\n", ray_x);
	if (info->ray_angle == 0 || info->ray_angle == WEST)
	{
		hit = 1;
		ray_x = p_x;
		ray_y = p_y;
	}
	while (hit == 0)
	{
		map_y = (int)ray_y / 64;
		map_x = (int)ray_x / 64;
		printf("map_x %d\nmap_y %d\n", map_x, map_y);
		if (map_x >= 0 && map_y >= 0 && map_x < 5 && map_y < 5)
			break ;
		if (arr[map_y][map_x] == 1)
		{	
			info->distance_v = ray_length(p_x, p_y, ray_x, ray_y);
			hit = 1;
		}
		ray_x += step_x;
		ray_y += step_y;
	}
}

void	check_vertical_hit(int p_x, int p_y, double step_x, double step_y, t_rayinfo *info)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	ray_y;
	double	ray_x;
	int		map_y;
	int		map_x;
	int		hit;

	hit = 0;
	if (info->ray_angle > NORTH && info->ray_angle < SOUTH)
	{
		ray_x = floor(p_x / 64) * 64 + 64;
		printf("ray_x %f\n", ray_x);
		step_x = 64;
	}
	if (info->ray_angle < NORTH || info->ray_angle > SOUTH)
	{
		ray_x = floor(p_x / 64) * 64 - 1;
		printf("ray_x %f\n", ray_x);
		step_x = -64;
	}
	ray_y = p_y + (p_x - (int)ray_x) * tan(info->ray_angle * PI / 180);
	printf("ray_y %f\n", ray_y);
	step_y = 64 * floor(tan(info->ray_angle * PI / 180));
	printf("step_y %f\n", step_y);
	if (info->ray_angle == NORTH || info->ray_angle == SOUTH)
	{
		hit = 1;
		ray_x = p_x;
		ray_y = p_y;
	}
	while (hit == 0)
	{
		map_y = (int)ray_y / 64;
		map_x = (int)ray_x / 64;
		printf("map_x %d\nmap_y %d\n", map_x, map_y);
		if (map_x >= 0 && map_y >= 0 && map_x < 5 && map_y < 5)
			break ;
		if (arr[map_y][map_x] == 1)
		{	
			info->distance_v = ray_length(p_x, p_y, ray_x, ray_y);
			hit = 1;
		}
		ray_x += step_x;
		ray_y += step_y;
	}
}

void	cast_rays(t_rayinfo *info)
{
	//int 	arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int		player_x;
	int		player_y;
	double	step_x;
	double	step_y;
	int		i;

	i = 0;
	info->ray_angle = info->angle - DEGREE * (FOV / 2);
	step_x = 0;
	step_y = 0;
	player_x = info->player->instances[0].x;
	player_y = info->player->instances[0].y;
	while (i < FOV)
	{
		check_horizontal_hit(player_x, player_y, step_x, step_y, info);
		check_vertical_hit(player_x, player_y, step_x, step_y, info);
		info->ray_angle += DEGREE;
		i++;
	}

}

void	key_hook_move(mlx_key_data_t keydata, void* param)
{
	t_rayinfo	*info;

	info = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle += DEGREE * 2;
		if (info->angle > 2 * 180)
			info->angle -= 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
		cast_rays(info);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle -= DEGREE * 2;
		if (info->angle < 0)
			info->angle += 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
		cast_rays(info);
	}
	printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].x += (int)info->playerdir_y;
		cast_rays(info);
	}
	printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].x -= (int)info->playerdir_y;
		cast_rays(info);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].y -= (int)info->playerdir_y;
		cast_rays(info);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].y += (int)info->playerdir_y;
		cast_rays(info);
	}
	printf("%d x: \n%d y: ", info->player->instances->x, info->player->instances->y);
	//if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		//mlx_close_window(param);
}

int32_t	main(void)
{
	// Start mlx
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int	i = 0;
	int	j = 0;
	t_rayinfo	rayinfo;

	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        error();
	memset(&rayinfo, 0, sizeof(t_rayinfo));
	mlx_image_t* black = mlx_new_image(mlx, 63, 63);
	if (!black)
		error();
	rayinfo.player = mlx_new_image(mlx, 8, 8);
	if (!rayinfo.player)
		error();
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		error();
	rayinfo.screen = screen;
	rayinfo.angle = 60;
	rayinfo.playerdir_x = cos(rayinfo.angle * PI / 180) * 10;
	rayinfo.playerdir_y = sin(rayinfo.angle * PI / 180) * 10;
	memset(black->pixels, 100, 64 * 64 * sizeof(int32_t));
	memset(rayinfo.player->pixels, 127, 8 * 8 * sizeof(int32_t));
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
        error();
	while (j < 5)
	{
		while (i < 5)
		{
			if (arr[j][i] == 1)
			{
				if (mlx_image_to_window(mlx, black, i * 64, j * 64) < 0)
        			error();
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (mlx_image_to_window(mlx, rayinfo.player, 96, 224) < 0)
		error();
	mlx_key_hook(mlx, &key_hook_move, &rayinfo);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}