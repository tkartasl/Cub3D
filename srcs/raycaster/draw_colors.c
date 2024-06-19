/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:13:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/18 16:14:29 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	draw_ceiling(t_data *data)
{
	int	x;
	int	red;
	int	green;
	int	blue;
	int	y;

	y = 0;
	red = *(int *)vec_get(data->parser->ceiling, 0);
	green = *(int *)vec_get(data->parser->ceiling, 1);
	blue = *(int *)vec_get(data->parser->ceiling, 2);
	while (y < HEIGHT/2)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->screen, x, y, get_rgba(red, green, blue, 210));
			++x;
		}
		++y;
	}
	return (y);
}

void	draw_floor(t_data *data, int y)
{
	int	x;
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(data->parser->floor, 0);
	green = *(int *)vec_get(data->parser->floor, 1);
	blue = *(int *)vec_get(data->parser->floor, 2);
	
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_put_pixel(data->screen, x, y, get_rgba(red, green, blue, 210));
			++x;
		}
		++y;
	}
}

void	draw_colors(t_data *data)
{
	int	y;

	y = draw_ceiling(data);
	draw_floor(data, y);
}
