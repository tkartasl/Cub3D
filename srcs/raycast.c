/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/03 15:05:20 by tkartasl         ###   ########.fr       */
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
#define DEGREE 0.01745329251
typedef struct s_rayinfo
{
	mlx_t* mlx;
	mlx_image_t* black;
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

void	draw_line(int x_end, int y_end, int x_start, int y_start, mlx_image_t * screen)
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
}

double	check_vertical_hit(double px, double py, t_rayinfo *info, double *vx, double *vy)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	ray_y = 0;
	double	ray_x = 0;
	int		viewdist;
	double	step_x = 0;
	double	step_y = 0;
	int		map_x = 0;
	int		map_y = 0;
	double	ntan = 0;
	double	dist_v = 100000;
	int		height = 5;
	int		width = 5;

	viewdist = 0;
	ntan = -tan(info->rayangle);
	if (info->rayangle > PI2 && info->rayangle < PI3)
	{
		ray_x = (((int)px >> 6) << 6) - 0.0001;
		ray_y = (px - ray_x) * ntan + py;
		step_x = -64;
		step_y = -step_x * ntan;
	}
	if (info->rayangle < PI2 || info->rayangle > PI3)
	{
		ray_x = (((int)px >> 6) << 6) + 64;
		ray_y = (px - ray_x) * ntan + py;
		step_x = 64;
		step_y = -step_x * ntan;
	}
	if (info->rayangle == 0 || info->rayangle == PI)
	{
		ray_x = px;
		ray_y = py;
		viewdist = 8;
	}
	while (viewdist < 8)
	{
		map_x = (int)ray_x >> 6;				
		map_y = (int)ray_y >> 6;
		if ((map_x >= 0 && map_x < width) && (map_y >= 0 && map_y < height) && arr[map_y][map_x] == 1)
		{
			//printf("mapv_x = %d\nmapv_y = %d\n", mapv_x, mapv_y);
			*vx = ray_x;
			*vy = ray_y;
			dist_v = ray_length(px, py, ray_x, ray_y);
			viewdist = 8;
		}
		else
		{
			ray_x += step_x;
			ray_y += step_y;
			viewdist += 1;
			}
		}
		return (dist_v);
}

double	check_horizontal_hit(double px, double py, t_rayinfo *info, double *hx, double *hy)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	ray_y = 0;
	double	ray_x = 0;
	int		viewdist;
	double	step_x = 0;
	double	step_y = 0;
	int		map_x = 0;
	int		map_y = 0;
	double	atan = 0;
	double	dist_h = 100000;
	int		height = 5;
	int		width = 5;

	viewdist = 0;
	atan = -1 / tan(info->rayangle);
	if (info->rayangle > PI)
	{
		ray_y = (((int)py >> 6) << 6) - 0.0001;
		ray_x = (py - ray_y) * atan + px;
		step_y = -64;
		step_x = -step_y * atan;
		}
		if (info->rayangle < PI)
		{
			ray_y = (((int)py >> 6) << 6) + 64;
			ray_x = (py - ray_y) * atan + px;
			step_y = 64;
			step_x = -step_y * atan;
		}
		if (info->rayangle == PI || info->rayangle == 0)
		{
			ray_x = px;
			ray_y = py;
			viewdist = 8;
		}
		while (viewdist < 8)
		{
			map_x = (int)ray_x >> 6;				
			map_y = (int)ray_y >> 6;
			if ((map_x >= 0 && map_x < width) && (map_y >= 0 && map_y < height) && arr[map_y][map_x] == 1)
			{
				//printf("maph_x = %d\nmaph_y = %d\n", maph_x, maph_y);
				*hx = ray_x;
				*hy = ray_y;
				dist_h = ray_length((double)info->player->instances[0].x, (double)info->player->instances[0].y, ray_x, ray_y);
				viewdist = 8;
			}
			else
			{
				ray_x += step_x;
				ray_y += step_y;
				viewdist += 1;
			}
		}
		return (dist_h);
}

void	cast_rays(t_rayinfo *info)
{
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	double	dist_h = 0;
	double	dist_v = 0;
	int		i = 0;
	double	px = info->player->instances[0].x;
	double 	py = info->player->instances[0].y;
	double	hx = 0;
	double 	vx = 0;
	double	hy = 0;
	double 	vy = 0;
	int		j = 0;

	mlx_image_t* screen = mlx_new_image(info->mlx, 320, 320);
	if (!screen)
		error();
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(info->mlx, screen, 0, 0) < 0)
    	error();
	while (j < 5)
	{
		while (i < 5)
		{
			if (arr[j][i] == 1)
			{
				if (mlx_image_to_window(info->mlx, info->black, i * 64, j * 64) < 0)
        			error();
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (mlx_image_to_window(info->mlx, info->player, info->player->instances[0].x, info->player->instances[0].y) < 0)
		error();
	info->rayangle = info->angle - DEGREE * FOV / 2;
	if (info->rayangle < 0)
		info->rayangle += 2 * PI;
	if (info->rayangle > 2 * PI)
		info->rayangle -= 2 * PI;
	while (i < FOV)
	{
		dist_h = check_horizontal_hit(px, py, info, &hx, &hy);
		dist_v = check_vertical_hit(px, py, info, &vx, &vy);
		printf("dist_h %f\ndist_v %f\n", dist_h, dist_v);
		if (dist_v >= dist_h)
			draw_line(px, py, hx, hy, screen);
		else
			draw_line(px, py, vx, vy, screen);
		info->rayangle += DEGREE;
		if (info->rayangle < 0)
			info->rayangle += 2 * PI;
		if (info->rayangle > 2 * PI)
			info->rayangle -= 2 * PI;
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
		//info->rayangle = info->angle;
		info->playerdir_x = cos(info->angle) * 10;
		info->playerdir_y = sin(info->angle) * 10;
	//	cast_rays(info);
	}
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->angle -= 0.2;
		if (info->angle < 0)
			info->angle += 2 * PI;
		//info->rayangle = info->angle;
		info->playerdir_x = cos(info->angle) * 10;
		info->playerdir_y = sin(info->angle) * 10;
	//	cast_rays(info);
	}
	//printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		//info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].x += (int)info->playerdir_y;
		cast_rays(info);
	}
	//printf("player dir x %f , player dir y %f\n" ,info->playerdir_x, info->playerdir_y);
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		//info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].x -= (int)info->playerdir_y;
		cast_rays(info);
	}
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x += (int)info->playerdir_x;
		info->player->instances[0].y += (int)info->playerdir_y;
		cast_rays(info);
	}
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT || keydata.action == MLX_PRESS))
	{
		info->player->instances[0].x -= (int)info->playerdir_x;
		info->player->instances[0].y -= (int)info->playerdir_y;
		cast_rays(info);
	}
	//printf("%d x: \n%d y: ", info->player->instances->x, info->player->instances->y);
	//if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		//mlx_close_window(param);
}

int32_t	main(void)
{
	// Start mlx
	int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int	i = 0;
	int	j = 0;
	t_rayinfo	rayinfo;

	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        error();
	memset(&rayinfo, 0, sizeof(t_rayinfo));
	rayinfo.mlx = mlx;
	mlx_image_t* black = mlx_new_image(mlx, 63, 63);
	if (!black)
		error();
	rayinfo.player = mlx_new_image(mlx, 4, 4);
	if (!rayinfo.player)
		error();
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		error();
	rayinfo.screen = screen;
	rayinfo.black = black;
	rayinfo.player = rayinfo.player;
	rayinfo.angle = 290 * PI / 180;
	rayinfo.rayangle = rayinfo.angle;
	rayinfo.playerdir_x = cos(rayinfo.angle) * 10;
	rayinfo.playerdir_y = sin(rayinfo.angle) * 10;
	memset(black->pixels, 100, 64 * 64 * sizeof(int32_t));
	memset(rayinfo.player->pixels, 127, 4 * 4 * sizeof(int32_t));
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
