/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:59:04 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/01 15:01:03 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	draw_line(int x, int y, t_data *data)
{
	mlx_texture_t	*wall;
	uint32_t 		pixel;
	int				offset;
	int				t_size;

	t_size = data->texture->wall[data->texture->idx]->height;
	pixel = 0;
	offset = 0;
	wall = data->texture->wall[data->texture->idx];
	offset = (((int)data->texture->y * t_size + (int)data->texture->x))
		 * sizeof(uint32_t);
	if (offset < (t_size * t_size * 4))
		pixel = (wall->pixels[offset] << 24) | (wall->pixels[offset + 1] << 16)
			| (wall->pixels[offset + 2] << 8) | wall->pixels[offset + 3];
	mlx_put_pixel(data->screen, x, y, pixel);
	data->texture->y += data->texture->ty_step;
}

void	get_texture_index(t_data *data, int x_pos, int t_size, t_vect *r)
{
	if (r->axis == 'x')
	{
		data->texture->x = ((int)r->x % t_size);
		if (r->angle < WEST)
		{
			data->texture->idx = NO;
			data->texture->x = t_size - data->texture->x;
		}
		else
			data->texture->idx = SO;
	}
	else
	{
		data->texture->x = ((int)r->y % t_size);
		if (r->angle > NORTH && r->angle < SOUTH)
		{
			data->texture->x = t_size - data->texture->x;
			data->texture->idx = EA;
		}
		else
			data->texture->idx = WE;
	}
}

void	draw_walls(t_data *data, int x, t_vect *r)
{
	double	start;
	int	y;

	start = (HEIGHT / 2) - (data->texture->height / 2);
	y = -1;
	while (++y < HEIGHT)
	{
		if (y <= start && (data->texture->height + start) < HEIGHT)
			draw_ceiling(data, x, y);
		else if (y > start && y <= (start + data->texture->height))
			draw_line(x, y, data);
		else if (y > (data->texture->height + start))
			draw_floor(data, x, y);
	}
	r->angle += DEGREE / ((double)WIDTH / FOV);
	reset_ray_angle(&r->angle);	
}
