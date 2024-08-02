/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:04:55 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/22 13:08:44 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_overflow(t_data *data)
{
	int	x;
	int	y;
	int	map_width;

	x = data->rayinfo->map_x;
	y = data->rayinfo->map_y;
	if (y < 0 || y >= data->map_height)
		return (1);
	map_width = *(int *)vec_get(data->map_width, y);
	if (x < 0 || x >= map_width)
		return (1);
	return (0);
}

void	reset_ray_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle >= 2 * PI)
		*angle -= 2 * PI;
}

double	ray_length(t_data *data, int horizontal)
{
	double	ax;
	double	ay;
	double	bx;
	double	by;

	ax = data->camera_x;
	ay = data->camera_y;
	if (horizontal)
	{
		bx = data->rayinfo->h_ray_x;
		by = data->rayinfo->h_ray_y;
	}
	else
	{
		bx = data->rayinfo->v_ray_x;
		by = data->rayinfo->v_ray_y;
	}
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
