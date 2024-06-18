/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:04 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/18 12:53:54 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
			mlx_put_pixel(data->screen, x_pos, y_start, get_rgba(255, 0, 0, color));
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
	line_end = (double)HEIGHT / 2 - line_h / 2;
	draw_line(x_pos, line_end, line_h + line_end, data, color);
	data->rayinfo->ray_angle += DEGREE / ((double)WIDTH / FOV);
	reset_ray_angle(&data->rayinfo->ray_angle);	
}
