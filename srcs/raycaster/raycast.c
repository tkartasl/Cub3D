/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/17 09:26:05 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	ray_length(t_data *data)
{
	double	ax;
	double	ay;
	double	bx;
	double	by;

	ax = data->camera_x;
	ay = data->camera_y;
	bx = data->rayinfo->ray_x;
	by = data->rayinfo->ray_y;
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

void	get_line_values(t_line *line, int x, int y_a, int y_b)
{
	line->delta_x = abs(x - x);
	line->slope_x = compare(x, x);
	line->delta_y = -abs(y_b - y_a);
	line->slope_y = compare(y_a, y_b);		
}

void	draw_line(int x_pos, int y_start, int y_end, t_data *data, int color)
{
	int	error;
	int	error2;

	get_line_values(data->line, x_pos, y_start, y_end);
	error = data->line->delta_x + data->line->delta_y;
	error2 = 0;
	while (1)
	{
		if (x_pos >= 0 && y_start >= 0 && x_pos < WIDTH && y_start < HEIGHT)
			mlx_put_pixel(data->screen, x_pos, y_start, color);
		if (y_start == y_end)
			break ;
		error2 = 2 * error;
		if (error2 >= data->line->delta_y)
		{
			error += data->line->delta_y;
			x_pos += data->line->slope_x;
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
	if (data->rayinfo->map_x < 0 || data->rayinfo->map_x >= data->map_width)
		i = 1;
	if (data->rayinfo->map_y < 0 || data->rayinfo->map_y >= data->map_height)
		i = 1;
	return (i);
}

double	check_vertical_hit(t_data *data)
{
	int		i;
	double	dist_v;
	int			map[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};

	dist_v = 1000000;
	i = 0;
	calculate_steps_v(data, &data->rayinfo->ray_y, &data->rayinfo->ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->ray_x >> 6;		
		data->rayinfo->map_y = (int)data->rayinfo->ray_y >> 6;
		if (check_overflow(data) == 0
			&& map[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			dist_v = ray_length(data);
			i = MAX_VIEW_DIST;
		}
		else
		{
			data->rayinfo->ray_x += data->rayinfo->step_x;
			data->rayinfo->ray_y += data->rayinfo->step_y;
			i += 1;
			}
		}
		return (dist_v);
}

double	check_horizontal_hit(t_data *data)
{
	int		i;
	double	dist;
	int			map[5][5] = {{1, 1, 1, 1, 1}, {1, 0, 0, 0, 1}, {1, 0, 1, 0, 1}, {1, 0, 0, 0, 1}, {1, 1, 1, 1, 1}};

	dist = 1000000;
	i = 0;
	calculate_steps_h(data, &data->rayinfo->ray_y, &data->rayinfo->ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->ray_x >> 6;				
		data->rayinfo->map_y = (int)data->rayinfo->ray_y >> 6;
		if (check_overflow(data) == 0
			&& map[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			dist = ray_length(data);
			i = MAX_VIEW_DIST;
		}
		else
		{
			data->rayinfo->ray_x += data->rayinfo->step_x;
			data->rayinfo->ray_y += data->rayinfo->step_y;
			i += 1;
		}
	}
	return (dist);
}

void	reset_ray_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
}

void	draw_walls(t_data *data, int color, int x_pos)
{
	double	line_h;
	double	line_end;
	double	correct_angle;

	correct_angle = data->player_angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->rayinfo->raydist = data->rayinfo->raydist * cos(correct_angle);
	line_h = (data->map_size * WIDTH) / data->rayinfo->raydist;
	if (line_h > WIDTH)
		line_h = WIDTH;
	line_end = HEIGHT / 2 - line_h / 2;
	draw_line(x_pos, line_end, line_h + line_end, data, color);
	data->rayinfo->ray_angle += DEGREE / (WIDTH / FOV);
	reset_ray_angle(&data->rayinfo->ray_angle);	
}

void	cast_rays(t_data *data)
{
	int		x_pos;
	int		color;

	color = 0;
	x_pos = 0;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	data->rayinfo->ray_angle = data->player_angle - DEGREE * FOV / 2;
	reset_ray_angle(&data->rayinfo->ray_angle);
	while (x_pos < WIDTH)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data);
		data->rayinfo->dist_v = check_vertical_hit(data);
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
		draw_walls(data, color, x_pos);
		x_pos++;
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
		data->camera_x += (int)data->playerdir_x;
		data->camera_y += (int)data->playerdir_y;
	}
	if (direction == 'A')
	{
		data->camera_x += (int)data->playerdir_y;
	}
	if (direction == 'S')
	{
		data->camera_x -= (int)data->playerdir_x;
		data->camera_y -= (int)data->playerdir_y;
	}
	if (direction == 'D')
	{
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

void	assign_values(t_data *data, t_line *line, t_rayinfo *rayinfo)
{
	data->player_angle = 270 * PI / 180;
	rayinfo->ray_angle = data->player_angle;
	data->rayinfo = rayinfo;
	data->line = line;
	data->playerdir_x = cos(data->player_angle) * 10;
	data->playerdir_y = sin(data->player_angle) * 10;
	data->map_width = 5;
	data->map_height = 5;
	data->map_size = 25;
	data->camera_x = 96;
	data->camera_y = 224;		
}

int32_t	main(void)
{
	t_data		data;
	t_rayinfo	rayinfo;
	t_line		line;

	ft_memset(&rayinfo, 0, sizeof(t_rayinfo));
	ft_memset(&line, 0, sizeof(t_line));
	ft_memset(&data, 0, sizeof(t_data));
	assign_values(&data, &line, &rayinfo);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
        error();
	data.mlx = mlx;
	mlx_image_t* screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		error();
	data.screen = screen;
	memset(data.screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		error();
	cast_rays(&data);
	mlx_key_hook(mlx, &key_hook_movement, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
