/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:13:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/08 13:01:50 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_ceiling(t_data *data, int x, int y)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(data->parser->ceiling, 0);
	green = *(int *)vec_get(data->parser->ceiling, 1);
	blue = *(int *)vec_get(data->parser->ceiling, 2);
	mlx_put_pixel(data->screen, x, y, get_rgba(red, green, blue, 210));
}

void	draw_floor(t_data *data, int x, int y)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(data->parser->floor, 0);
	green = *(int *)vec_get(data->parser->floor, 1);
	blue = *(int *)vec_get(data->parser->floor, 2);
	mlx_put_pixel(data->screen, x, y, get_rgba(red, green, blue, 210));
}
