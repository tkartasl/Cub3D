/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/30 13:11:37 by tkartasl         ###   ########.fr       */
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
typedef struct s_rayinfo
{
	mlx_image_t *player;
	mlx_image_t *screen;
	double	angle;
	double	playerdir_x;
	double	playerdir_y;
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

	x_start += 4;
	y_start += 8;
	printf("x_start: %d\n", x_start);
	printf("y_start: %d\n", y_start);
	printf("x_end: %d\n", x_end);
	printf("y_end: %d\n", y_end);
	ye = 0;
	xe = 0;
	y = 0;
	x = 0;
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

void	cast_rays(t_rayinfo *info)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	ray_y = 0;
	double	ray_x = 0;
	//double	plane_x = 0;
	//double	plane_y = 0.66;
	//double	time = 0;
	//double	oldtime = 0;
	int		viewdist;
	//double	ray_count;
	double	step_x = 0;
	double	step_y = 0;
	int		map_x = 0;
	int		map_y = 0;
	double	rayangle = 0;
	double	atan = 0;
	double	ntan = 0;
	double	dist_h = 100000;
	double	dist_v = 100000;
	int		i = 0;
	int	height = 5;
	int	width = 5;

	while (i < 1)
	{
		viewdist = 0;
		rayangle = info->angle * PI / 180;
		atan = -1/tan(rayangle);
		if (rayangle > PI)
		{
			ray_y = ((info->player->instances[0].y >> 6) << 6) - 0.0001;
			ray_x = (info->player->instances[0].y - ray_y) * atan + info->player->instances[0].x;
			step_y = -64;
			step_x = -step_y * atan;
		}
		if (rayangle < PI)
		{
			ray_y = ((info->player->instances[0].y >> 6) << 6) + 64;
			ray_x = (info->player->instances[0].y - ray_y) * atan + info->player->instances[0].x;
			step_y = 64;
			step_x = -step_y * atan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			ray_x = info->player->instances[0].x;
			ray_y = info->player->instances[0].y;
			viewdist = 8;
		}
		while (viewdist < 8)
		{
			map_x = (int)ray_x >> 6;				
			map_y = (int)ray_y >> 6;
			if ((map_x > 0 && map_x < width) && (map_y > 0 && map_y < height) && arr[map_y][map_x] == 1)
			{
				dist_h = ray_length(info->player->instances[0].x, info->player->instances[0].y, ray_x, ray_y);
				viewdist = 8;
			}
			else
			{
				ray_x += step_x;
				ray_y += step_y;
				viewdist += 1;
			}
		}
		viewdist = 0;
		rayangle = info->angle;
		ntan = -tan(rayangle);
		if (rayangle > PI2 && rayangle < PI3)
		{
			ray_x = ((info->player->instances[0].x >> 6) << 6) - 0.0001;
			ray_y = (info->player->instances[0].x - ray_x) * ntan + info->player->instances[0].y;
			step_x = -64;
			step_y = -step_x * ntan;
		}
		if (rayangle < PI2 || rayangle > PI3)
		{
			ray_x = ((info->player->instances[0].x >> 6) << 6) + 64;
			ray_y = (info->player->instances[0].x - ray_x) * ntan + info->player->instances[0].y;
			step_x = 64;
			step_y = -step_x * ntan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			ray_x = info->player->instances[0].x;
			ray_y = info->player->instances[0].y;
			viewdist = 8;
		}
		while (viewdist < 8)
		{
			map_x = (int)ray_x >> 6;				
			map_y = (int)ray_y >> 6;
			if ((map_x > 0 && map_x < width) && (map_y > 0 && map_y < height) && arr[map_y][map_x] == 1)
			{
				dist_v = ray_length(info->player->instances[0].x, info->player->instances[0].y, ray_x, ray_y);
				viewdist = 8;
			}
			else
			{
				ray_x += step_x;
				ray_y += step_y;
				viewdist += 1;
			}
		}
		draw_line(info->player->instances[0].x, info->player->instances[0].y, (int)ray_x, (int)ray_y, info->screen);
		i++;
	}
}

void	key_hook_move(mlx_key_data_t keydata, void* param)
{
	t_rayinfo	*info;

	info = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle += 1.8 * 2;
		if (info->angle > 2 * 180)
			info->angle -= 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
		//cast_rays(info);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle -= 1.8 * 2;
		if (info->angle < 0)
			info->angle += 2 * 180;
		info->playerdir_x = cos(info->angle * PI / 180) * 10;
		info->playerdir_y = sin(info->angle * PI / 180) * 10;
		//cast_rays(info);
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
	//mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	//if (!w)
	//	error();
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
	rayinfo.angle = 90;
	rayinfo.playerdir_x = cos(rayinfo.angle * PI / 180) * 10;
	rayinfo.playerdir_y = sin(rayinfo.angle * PI / 180) * 10;
	//memset(white->pixels, 255, 360 * 360 * sizeof(int32_t));
	//memset(player->pixels, 127, 8 * 8 * sizeof(int32_t));	
	//memset(white->pixels, 255, 64 * 64 * sizeof(int32_t));
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
	// Optional, terminate will clean up any leftovers, this is just to demonstrate.
	mlx_delete_image(mlx, screen);
	mlx_delete_image(mlx, black);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}