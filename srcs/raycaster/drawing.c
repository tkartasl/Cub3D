/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:04 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/19 13:49:04 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"
#include <stdint.h>

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
	uint32_t	color;
	int		offset;
	mlx_texture_t	*wall;

	color = 0;
	wall = texture->wall[texture->idx];
	if (x_pos > 64)
		x_pos = x_pos % 64;
	if (y_start > 64)
		y_start = y_start % 64;
	offset = ((y_start * wall->width) + x_pos) * wall->bytes_per_pixel;
	color += wall->pixels[offset];
	color = color << 8;
	color += wall->pixels[offset + 1];
	color = color << 8;
	color += wall->pixels[offset + 2];
	color = color << 8;
	color += wall->pixels[offset + 3];
	return (color);
}

void	draw_line(int x_pos, int y_start, int y_end, t_data *data)
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
}

void	get_texture_index(t_data *data)
{
	if (data->texture->axis == 'x' && data->playerdir_y < 0)
		data->texture->idx = NO;
	else if (data->texture->axis == 'x' && data->playerdir_y > 0)
		data->texture->idx = SO;
	else if (data->texture->axis == 'y' && data->playerdir_x > 0)
		data->texture->idx = EA;
	else if (data->texture->axis == 'y' && data->playerdir_x < 0)
		data->texture->idx = WE;
}

void	draw_end_wall(t_data *data, double wall_height, int x_pos)
{

}

void	draw_walls(t_data *data, int x_pos)
{
	double	height;
	double	start;
	double	correct_angle;

	correct_angle = data->player_angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->rayinfo->raydist = data->rayinfo->raydist * cos(correct_angle);
//	line_h = (WIDTH) / data->rayinfo->raydist;
	height = (data->map_size * 100) / data->rayinfo->raydist;
	if (height >= WIDTH)
		height = WIDTH;
		//draw_end_wall(data, height, x_pos);
	start = (double)HEIGHT / 2 - height / 2;
	get_texture_index(data);
	draw_line(x_pos, start, height + start, data);
	data->rayinfo->ray_angle += DEGREE / ((double)WIDTH / FOV);
	reset_ray_angle(&data->rayinfo->ray_angle);	
}
