/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:13:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/19 11:14:18 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	draw_ceiling(t_data *data, int x, int y)
{
	mlx_put_pixel(data->screen, x, y, get_rgba(data->ccolors[R], data->ccolors[G], data->ccolors[B], 210));
}

void	draw_floor(t_data *data, int x, int y)
{
	mlx_put_pixel(data->screen, x, y, get_rgba(data->fcolors[R], data->fcolors[G], data->fcolors[B], 210));
}
