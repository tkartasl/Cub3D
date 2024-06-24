/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:04 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/19 16:49:04 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_ceiling(t_data *data, int x, int y);
void	draw_floor(t_data *data, int x, int y);

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

int	get_texture_pixel(t_textures *texture, int x_pos, int y_start)
{
	uint32_t		color;
	int				offset;
	mlx_texture_t	*wall;

	wall = texture->wall[texture->idx];
	if (x_pos > 64)
		x_pos = x_pos % 64;
	if (y_start > 64)
		y_start = y_start % 64;
	offset = ((y_start * wall->width) + x_pos) * wall->bytes_per_pixel;
	//printf("offset: %d, width: %d, height: %d\n", offset, wall->width, wall->height);
//	offset = x_pos * sizeof(uint32_t) + y_start * wall->width * sizeof(uint32_t);
	color = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16) | (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 3];
	return (color);
}

void	draw_line(int x, int y, int height, t_data *data, int texture_x, int start_y)
{
	int	error;
	double	r;
	mlx_texture_t	*wall;
	int		texture_y;

	wall = data->texture->wall[data->texture->idx];
	if (height > HEIGHT)
		height = HEIGHT;
	r = (double)y / (double)height;
	texture_y = ((wall->height - 1 - (2 * start_y))  * r) + start_y;
	mlx_put_pixel(data->screen, x, y, get_texture_pixel(data->texture, x, texture_y));
}

int	get_texture_index(t_data *data, int wall_height, int x_pos)
{
	int	texture_x;
	double	r;
	double	vec_val;
	double		screen_position;
	int	x;
	int	y;

	screen_position = 2 * (double) x_pos / (double) WIDTH - 1;
	x = data->camera_x + data->playerdir_x * screen_position;
	y = data->camera_y + data->playerdir_y * screen_position;
	if (data->texture->axis == 'x')
	{
		if (data->rayinfo->ray_angle < WEST)
			data->texture->idx = NO;
		else
			data->texture->idx = SO;
		vec_val = data->camera_x + data->rayinfo->raydist * x;
		r = vec_val - floor(vec_val);
	}
	else
	{
		if (data->rayinfo->ray_angle > NORTH && data->rayinfo->ray_angle < SOUTH)
			data->texture->idx = EA;
		else
			data->texture->idx = WE;
		vec_val = data->camera_y + data->rayinfo->raydist * y;
		r = vec_val - floor(vec_val);
	}
	texture_x = round(r * (double)data->texture->wall[data->texture->idx]->width); 
	return (texture_x);
}

void	draw_walls(t_data *data, int x_pos)
{
	double	height;
	double	start;
	double	correct_angle;
	int	y;
	int	texture_x;
	int	texture_y;

	texture_y = 0;
	correct_angle = data->player_angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->rayinfo->raydist = data->rayinfo->raydist * cos(correct_angle);
	height = (data->map_size * HEIGHT) / data->rayinfo->raydist;
	if (height >= HEIGHT)
		texture_y = ((double)(height - HEIGHT) / 2.0)
				/ ((double)height * (double)data->texture->wall[data->texture->idx]->height);
	start = (int)((double)HEIGHT / 2) - (height / 2);
	y = -1;
	texture_x = get_texture_index(data, height, x_pos);
	while (++y < HEIGHT)
	{
		if (y < start && (height + start) < HEIGHT)
			draw_ceiling(data, x_pos, y);
		else if (y > start && y <= (start + height))
			draw_line(x_pos, y, start + height, data, texture_x, texture_y);
		else if (y > (height + start))
			draw_floor(data, x_pos, y);
	}
	data->rayinfo->ray_angle += DEGREE / ((double)WIDTH / FOV);
	reset_ray_angle(&data->rayinfo->ray_angle);	
}
