/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:04:55 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/21 12:07:47 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_overflow(t_data *data)
{
	int	i;
	int	x;
	int	y;
	
	i = 0;
	x = data->rayinfo->map_x;
	y = data->rayinfo->map_y;
	if (y < 0 || y >= data->map_height)
		i = 1;
	if (x < 0 || i == 1 || x >= ft_strlen(data->map[y]))
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
