/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/05/31 16:06:28 by tkartasl         ###   ########.fr       */
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
#define	FOV	60
#define EAST 0
#define NORTH PI / 2
#define WEST PI
#define SOUTH 3 * PI / 2

typedef struct s_mlx
{
	mlx_t* mlx;
	mlx_image_t* black;
 	mlx_image_t* screen;
	mlx_image_t* player;
}			t_mlx_stuff;

typedef struct s_rayinfo
{
	mlx_image_t *player;
	mlx_image_t *screen;
	double	angle;
	double	rayangle;
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

int	compare(int a, int b)
{
	int	ret;

	if (a < b)
		ret = 1;
	else
		ret = -1;
	return (ret);
}

void	draw_line(int x_end, int y_end, int x_start, int y_start, mlx_image_t *screen)
{
	int dx = abs(x_end - x_start);
	int	sx = compare(x_start, x_end);
	int dy = -abs(y_end - y_start);
	int	sy = compare(y_start, y_end);
	int	err = dx + dy;
	int	e2;

	e2 = 0;
	while (1)
	{
		if (x_start >= 0 && y_start >= 0 && x_start <= 320 && y_start <= 320)
			mlx_put_pixel(screen, x_start, y_start, 155);
		if (x_start == x_end && y_start == y_end)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x_start += sx;
		}	
		if (e2 <= dx)
		{
			err += dx;
			y_start += sy;
		}
	}
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
}

void	cast_rays(t_rayinfo *info)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	rayh_y = 0;
	double	rayh_x = 0;
	double	rayv_y = 0;
	double	rayv_x = 0;
	//double	plane_x = 0;
	//double	plane_y = 0.66;
	//double	time = 0;
	//double	oldtime = 0;
	int		viewdist;
	//double	ray_count;
	double	step_x = 0;
	double	step_y = 0;
	int		maph_x = 0;
	int		maph_y = 0;
	int		mapv_x = 0;
	int		mapv_y = 0;
	double	atan = 0;
	double	ntan = 0;
	double	dist_h = 100000;
	double	dist_v = 100000;
	int		i = 0;
	int		height = 5;
	int		width = 5;
	
	while (i < 1)
	{
		viewdist = 0;
		atan = -1/tan(rayangle);
		if (rayangle > WEST)
		{
			rayh_y = ((info->player->instances[0].y >> 6) << 6) - 0.0001;
			rayh_x = (info->player->instances[0].y - rayh_y) * atan + info->player->instances[0].x;
			step_y = -64;
			step_x = -step_y * atan;
		}
		if (rayangle < WEST)
		{
			rayh_y = ((info->player->instances[0].y >> 6) << 6) + 64;
			rayh_x = (info->player->instances[0].y - rayh_y) * atan + info->player->instances[0].x;
			step_y = 64;
			step_x = -step_y * atan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			rayh_x = info->player->instances[0].x;
			rayh_y = info->player->instances[0].y;
			viewdist = 8;
		}
		while (viewdist < 8)
		{
			maph_x = (int)rayh_x >> 6;				
			maph_y = (int)rayh_y >> 6;
			printf("maph_x = %d\nmaph_y = %d\n", maph_x, maph_y);
			if ((maph_x >= 0 && maph_x < width) && (maph_y >= 0 && maph_y < height) && arr[maph_y][maph_x] == 1)
			{
				dist_h = ray_length(info->player->instances[0].x, info->player->instances[0].y, rayh_x, rayh_y);
				viewdist = 8;
			}
			else
			{
				rayh_x += step_x;
				rayh_y += step_y;
				viewdist += 1;
			}
		}
		viewdist = 0;
		ntan = -tan(rayangle);
		if (rayangle > NORTH && rayangle < SOUTH)
		{
			rayv_x = ((info->player->instances[0].x >> 6) << 6) - 0.0001;
			rayv_y = (info->player->instances[0].x - rayv_x) * ntan + info->player->instances[0].y;
			step_x = -64;
			step_y = -step_x * ntan;
		}
		if (rayangle < NORTH || rayangle > SOUTH)
		{
			rayv_x = ((info->player->instances[0].x >> 6) << 6) + 64;
			rayv_y = (info->player->instances[0].x - rayv_x) * ntan + info->player->instances[0].y;
			step_x = 64;
			step_y = -step_x * ntan;
		}
		if (rayangle == 0 || rayangle == PI)
		{
			rayv_x = info->player->instances[0].x;
			rayv_y = info->player->instances[0].y;
			viewdist = 8;
		}
		while (viewdist < 8)
		{
			mapv_x = (int)rayv_x >> 6;				
			mapv_y = (int)rayv_y >> 6;
			printf("mapv_x = %d\nmapv_y = %d\n", mapv_x, mapv_y);
			if ((mapv_x >= 0 && mapv_x < width) && (mapv_y >= 0 && mapv_y < height) && arr[mapv_y][mapv_x] == 1)
			{
				dist_v = ray_length(info->player->instances[0].x, info->player->instances[0].y, rayv_x, rayv_y);
				viewdist = 8;
			}
			else
			{
				rayv_x += step_x;
				rayv_y += step_y;
				viewdist += 1;
			}
		}
		printf("dist_h = %f\ndist_v = %f\n", dist_h, dist_v);
		if (dist_h >= dist_v)
			draw_line(info->player->instances[0].x, info->player->instances[0].y, (int)rayv_x, (int)rayv_y, info->screen);
		else
			draw_line(info->player->instances[0].x, info->player->instances[0].y, (int)rayh_x, (int)rayh_y, info->screen);
		//info->ray_angle
		i++;
	}
}

void	key_hook_move(mlx_key_data_t keydata, void* param)
{
	t_rayinfo	*info;

	info = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle += 0.2;
		if (info->angle > 2 * PI)
			info->angle -= 2 * PI;
		info->playerdir_x = cos(info->angle) * 10;
		info->playerdir_y = sin(info->angle) * 10;
		//cast_rays(info);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle -= 0.2;
		if (info->angle < 0)
			info->angle += 2 * PI;
		info->playerdir_x = cos(info->angle) * 10;
		info->playerdir_y = sin(info->angle) * 10;
		//cast_rays(info);
	}
	//printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].x += (int)info->playerdir_y;
		cast_rays(info);
	}
	//printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
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
	//printf("%d x: \n%d y: ", info->player->instances->x, info->player->instances->y);
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
	t_mlx_stuff	imgs;

	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        error();
	memset(&rayinfo, 0, sizeof(t_rayinfo));
	memset(&imgs, 0, sizeof(t_mlx_stuff));
	imgs.mlx = mlx;
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
	imgs.black = black;
	imgs.screen = screen;
	imgs.player = rayinfo.player;
	rayinfo.angle = 120 * PI / 180;
	rayinfo.rayangle = rayinfo.angle;
	rayinfo.playerdir_x = cos(rayinfo.angle) * 10;
	rayinfo.playerdir_y = sin(rayinfo.angle) * 10;
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
	mlx_delete_image(mlx, screen);
	mlx_delete_image(mlx, black);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
