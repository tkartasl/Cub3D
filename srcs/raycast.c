/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/06 12:18:35 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
/*#include "../MLX42/include/MLX42/MLX42.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#define PI 3.14159265359
#define	FOV	60
#define EAST 0
#define NORTH PI / 2
#define WEST PI
#define SOUTH 3 * PI / 2
#define DEGREE 0.01745329251
#define MAX_VIEW_DIST 8

typedef	struct s_rayinfo
{
	double	dist_h;
	double	dist_v;
	double	raydist;
	double	ray_angle;
	double	ntan;
	double	atan;
	double	step_x;
	double	step_y;	
	int		map_x;
	int		map_y;
	
}			t_rayinfo;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*black;
	mlx_image_t *player;
	mlx_image_t *screen;
	double		player_angle;
	double		playerdir_x;
	double		playerdir_y;
	int			height;
	int			width;
	t_rayinfo	*rayinfo;
}			t_data;*/

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	ray_length(double ax, double ay, double bx, double by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
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

void	get_line_values(t_line *line, int x_a, int y_a, int x_b, int y_b)
{
	line->delta_x = abs(x_b - x_a);
	line->slope_x = compare(x_a, x_b);
	line->delta_y = -abs(y_b - y_a);
	line->slope_y = compare(y_a, y_b);		
}

void	draw_line(int x_start, int y_start, int x_end, int y_end, t_data *data, int color)
{
	int	error;
	int	error2;

	get_line_values(data->line, x_start, y_start, x_end, y_end);
	error = data->line->delta_x + data->line->delta_y;
	error2 = 0;
	while (1)
	{
		if (x_start >= 0 && y_start >= 0 && x_start <= 320 && y_start <= 320)
			mlx_put_pixel(data->screen, x_start, y_start, color);
		if (x_start == x_end && y_start == y_end)
			break ;
		error2 = 2 * error;
		if (error2 >= data->line->delta_y)
		{
			error += data->line->delta_y;
			x_start += data->line->slope_x;
		}	
		if (error2 <= data->line->delta_x)
		{
			error += data->line->delta_x;
			y_start += data->line->slope_y;
		}
	}
}

void	calculate_steps_v(t_data *data, double *ray_y, double *ray_x, int *i)
{
	int	py;
	int	px;

	px = data->camera_x;
	py = data->camera_y;
	data->rayinfo->ntan = -tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > NORTH && data->rayinfo->ray_angle < SOUTH)
	{
		*ray_x = (((int)px >> 6) << 6) - 0.0001;
		*ray_y = (px - *ray_x) * data->rayinfo->ntan + py;
		data->rayinfo->step_x = -64;
	}
	if (data->rayinfo->ray_angle < NORTH || data->rayinfo->ray_angle > SOUTH)
	{
		*ray_x = (((int)px >> 6) << 6) + 64;
		*ray_y = (px - *ray_x) * data->rayinfo->ntan + py;
		data->rayinfo->step_x = 64;
	}
	data->rayinfo->step_y = -data->rayinfo->step_x * data->rayinfo->ntan;
	if (data->rayinfo->ray_angle == 0 || data->rayinfo->ray_angle == WEST)
	{
		*ray_x = px;
		*ray_y = py;
		*i = MAX_VIEW_DIST;
	}
}

void	calculate_steps_h(t_data *data, double *ray_y, double *ray_x, int *i)
{
	int	py;
	int	px;

	px = data->camera_x;
	py = data->camera_y;
	data->rayinfo->atan = -1 / tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > WEST)
	{
		*ray_y = (((int)py >> 6) << 6) - 0.0001;
		*ray_x = (py - *ray_y) * data->rayinfo->atan + px;
		data->rayinfo->step_y = -64;
	}
	if (data->rayinfo->ray_angle < WEST)
	{
		*ray_y = (((int)py >> 6) << 6) + 64;
		*ray_x = (py - *ray_y) * data->rayinfo->atan + px;
		data->rayinfo->step_y = 64;
	}
	data->rayinfo->step_x = -data->rayinfo->step_y * data->rayinfo->atan;
	if (data->rayinfo->ray_angle == WEST || data->rayinfo->ray_angle == 0)
	{
		*ray_x = px;
		*ray_y = py;
		*i = MAX_VIEW_DIST;
	}
}

int	check_overflow(t_data *data)
{
	int	i;
	i = 0;
	if (data->rayinfo->map_x < 0 || data->rayinfo->map_x >= data->width)	
		i = 1;
	if (data->rayinfo->map_y < 0 || data->rayinfo->map_y >= data->height)
		i = 1;
	return (i);
}

double	check_vertical_hit(t_data *data, double *vx, double *vy)
{
	//int arr[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	int arr[5][6] = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};
	double	ray_y = 0;
	double	ray_x = 0;
	int		i;
	double	dist_v = 1000000;

	i = 0;
	calculate_steps_v(data, &ray_y, &ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)ray_x >> 6;				
		data->rayinfo->map_y = (int)ray_y >> 6;
		if (check_overflow(data) == 0 && arr[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			*vx = ray_x;
			*vy = ray_y;
			dist_v = ray_length(data->camera_x, data->camera_y, ray_x, ray_y);
			i = MAX_VIEW_DIST;
		}
		else
		{
			ray_x += data->rayinfo->step_x;
			ray_y += data->rayinfo->step_y;
			i += 1;
			}
		}
		return (dist_v);
}

double	check_horizontal_hit(t_data *data, double *hx, double *hy)
{
	//int arr[10][10] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
	int arr[5][6] = {{1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 1}, {1, 0, 0, 1, 0, 1}, {1, 0, 0, 0, 0, 1}, {1, 1, 1, 1, 1, 1}};
	double	ray_y = 0;
	double	ray_x = 0;
	int		i;
	double	dist = 1000000;

	i = 0;
	calculate_steps_h(data, &ray_y, &ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)ray_x >> 6;				
		data->rayinfo->map_y = (int)ray_y >> 6;
		if (check_overflow(data) == 0 && arr[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			*hx = ray_x;
			*hy = ray_y;
			dist = ray_length(data->camera_x, data->camera_y, ray_x, ray_y);
			i = MAX_VIEW_DIST;
		}
		else
		{
			ray_x += data->rayinfo->step_x;
			ray_y += data->rayinfo->step_y;
			i += 1;
		}
	}
	return (dist);
}

void	reset_ray_angle(double angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
}

void	cast_rays(t_data *data)
{
	//int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	int		i = 0;
	double	hx = 0;
	double 	vx = 0;
	double	hy = 0;
	double 	vy = 0;
//	double	j = 0;
	double	line_h = 0;
	//double	line_o = 0;
//	double	line_start;
	double	line_end;
	double	line_x;
	double	correct_angle;
	int	color = 0;

	correct_angle = 0;
	line_x = 0;
	memset(data->screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	/*mlx_image_t* screen = mlx_new_image(data->mlx, 320, 320);
	if (!screen)
		error();
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(data->mlx, screen, 0, 0) < 0)
		error();*/
	/*mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        return (1);
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		return (1);
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		return (1);*/
	/*while (j < 5)
	{
		while (i < 5)
		{
			if (arr[j][i] == 1)
			{
				if (mlx_image_to_window(data->mlx, data->black, i * 64, j * 64) < 0)
					error();
			}
			i++;
		}
		i = 0;
		j++;
	}
	if (mlx_image_to_window(data->mlx, data->player, data->player->instances[0].x, data->player->instances[0].y) < 0)
		error();*/
	data->rayinfo->ray_angle =  data->player_angle - DEGREE * FOV / 2;
	reset_ray_angle(correct_angle);
	while (i < FOV)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data, &hx, &hy);
		data->rayinfo->dist_v = check_vertical_hit(data, &vx, &vy);
		if (data->rayinfo->dist_v >= data->rayinfo->dist_h)
		{
			color = 150;
			data->rayinfo->raydist = data->rayinfo->dist_h;
		}
		if (data->rayinfo->dist_h >= data->rayinfo->dist_v)
		{
			color = 12;
			data->rayinfo->raydist = data->rayinfo->dist_v;
		}
		correct_angle = data->player_angle - data->rayinfo->ray_angle;
		reset_ray_angle(data->rayinfo->ray_angle);
		data->rayinfo->raydist = data->rayinfo->raydist * cos(correct_angle);
		line_h = (30 * 320) / data->rayinfo->raydist;
		if (line_h > 320)
			line_h = 320;
		//line_start = 160 + line_h / 2;
		line_end = 160 - line_h / 2;
		draw_line(i, line_end, i, line_h + line_end, data, color);
		//	draw_line(data->camera_x, data->camera_y, hx, hy, screen);
		data->rayinfo->ray_angle += DEGREE;
		reset_ray_angle(data->rayinfo->ray_angle);
		i++;
	}
}

void	rotate_player(t_data *data, char direction)
{
	if (direction == 'R' )
	{
		data->player_angle += 0.2;
		if (data->player_angle > 2 * PI)
			data->player_angle -= 2 * PI;
		data->playerdir_x = cos(data->player_angle) * 10;
		data->playerdir_y = sin(data->player_angle) * 10;
	}
	if (direction == 'L')
	{
		data->player_angle -= 0.2;
		if (data->player_angle < 0)
			data->player_angle += 2 * PI;
		data->playerdir_x = cos(data->player_angle) * 10;
		data->playerdir_y = sin(data->player_angle) * 10;
	}
}

void	move_player(t_data *data, char direction)
{
	if (direction == 'W')
	{
		//data->player->instances[0].x += (int)data->playerdir_x;
		//data->player->instances[0].y += (int)data->playerdir_y;
		data->camera_x += (int)data->playerdir_x;
		data->camera_y += (int)data->playerdir_y;
	}
	if (direction == 'A')
	{
		//data->player->instances[0].x += (int)data->playerdir_y;
		data->camera_x += (int)data->playerdir_y;
	}
	if (direction == 'S')
	{
	//	data->player->instances[0].x -= (int)data->playerdir_x;
	//	data->player->instances[0].y -= (int)data->playerdir_y;
		data->camera_x -= (int)data->playerdir_x;
		data->camera_y -= (int)data->playerdir_y;
	}
	if (direction == 'D')
	{
	//	data->player->instances[0].x -= (int)data->playerdir_y;
		data->camera_x -= (int)data->playerdir_y;
	}
}

void	key_hook_movement(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		rotate_player(data, 'R');
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		rotate_player(data, 'L');
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'W');
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'A');
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'S');
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'D');
	cast_rays(data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

int32_t	main(void)
{
	//int arr[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};
	//int	i = 0;
	//int	j = 0;
	t_data		data;
	t_rayinfo	rayinfo;
	t_line		line;
	
	mlx_t* mlx = mlx_init(320, 320, "Test", true);
	if (!mlx)
        error();
	memset(&data, 0, sizeof(t_data));
	memset(&rayinfo, 0, sizeof(t_rayinfo));
	memset(&line, 0, sizeof(t_line));
	data.mlx = mlx;
	/*mlx_image_t* black = mlx_new_image(mlx, 63, 63);
	if (!black)
		error();
	data.player = mlx_new_image(mlx, 4, 4);
	if (!data.player)
		error();*/
	mlx_image_t* screen = mlx_new_image(mlx, 320, 320);
	if (!screen)
		error();
	memset(screen->pixels, 255, 320 * 320 * sizeof(int32_t));
	data.screen = screen;
	//data.black = black;
	data.player_angle = 270 * PI / 180;
	rayinfo.ray_angle = data.player_angle;
	data.rayinfo = &rayinfo;
	data.line = &line;
	data.playerdir_x = cos(data.player_angle) * 10;
	data.playerdir_y = sin(data.player_angle) * 10;
	data.width = 5;
	data.height = 5;
	data.camera_x = 96;
	data.camera_y = 224;
	//memset(black->pixels, 100, 64 * 64 * sizeof(int32_t));
	//memset(data.player->pixels, 127, 4 * 4 * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		error();
	/*while (j < 5)
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
	if (mlx_image_to_window(mlx, data.player, 96, 224) < 0)
		error();*/
	mlx_key_hook(mlx, &key_hook_movement, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
