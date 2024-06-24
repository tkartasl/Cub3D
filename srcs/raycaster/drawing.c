/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:04 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/21 12:07:20 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <stdint.h>

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

	color = 0;
	wall = texture->wall[texture->idx];
	if (x_pos > 64)
		x_pos = x_pos % 64;
	if (y_start > 64)
		y_start = y_start % 64;
	//offset = ((x_pos * wall->width) + y_start) * (uint32_t)wall->bytes_per_pixel;
	offset = x_pos * sizeof(uint32_t) + y_start * wall->width * sizeof(uint32_t);
	color = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16) | (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 1];
	return (color);
}

int	draw_line(int x_pos, int y_start, int y_end, t_data *data)
{
	int	error;

	get_line_values(data->line, x_pos, y_start, y_end);
	error = data->line->delta_x + data->line->delta_y;
	while (1)
	{
		if (x_pos >= 0 && y_start >= 0 && x_pos < WIDTH && y_start < HEIGHT)
			mlx_put_pixel(data->screen, x_pos, y_start, get_texture_pixel(data->texture, x_pos, y_start));
		if (y_start == y_end)
			break ;
		data->line->error2 = 2 * error;
		if (data->line->error2 >= data->line->delta_y)
		{
			error += data->line->delta_y;
			x_pos += data->line->slope_x;
		}	
		if (data->line->error2 <= data->line->delta_x)
		{
			error += data->line->delta_x;
			y_start += data->line->slope_y;
		}
	}
	return (y_end);
}

void	get_texture_index(t_data *data)
{
	if (data->texture->axis == 'x')
	{
		if (data->rayinfo->ray_angle < WEST)
			data->texture->idx = NO;
		else
			data->texture->idx = SO;
	}
	else
	{
		if (data->rayinfo->ray_angle > NORTH
			&& data->rayinfo->ray_angle < SOUTH)
			data->texture->idx = WE;
		else
			data->texture->idx = EA;
	}
}

void	draw_walls(t_data *data, int x_pos)
{
	double	height;
	double	start;
	double	correct_angle;
	int	y;

	correct_angle = data->player_angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->rayinfo->raydist = data->rayinfo->raydist * cos(correct_angle);
	height = (64 / data->rayinfo->raydist) * 1108;//WIDTH / data->rayinfo->raydist;
	if (height > HEIGHT)
		height = HEIGHT;
	start = ((double)HEIGHT / 2) - (height / 2);
	y = -1;
	get_texture_index(data);
	while (++y < HEIGHT)
	{
		if (y < start && (height + start) < HEIGHT)
			draw_ceiling(data, x_pos, y);
		else if (y > start && y <= (start + height))
			y = draw_line(x_pos, start, height + start, data);
		else if (y > (height + start))
			draw_floor(data, x_pos, y);
	}
	data->rayinfo->ray_angle += DEGREE / ((double)WIDTH / FOV);
	reset_ray_angle(&data->rayinfo->ray_angle);	
}
