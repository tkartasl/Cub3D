/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:04:55 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/17 10:05:46 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	reset_ray_angle(double *angle)
{
	if (*angle < 0)
		*angle += 2 * PI;
	if (*angle > 2 * PI)
		*angle -= 2 * PI;
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
