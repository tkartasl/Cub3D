/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:04:55 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/28 14:05:18 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	check_overflow(t_data *data, int *map)
{
	int	x;
	int	y;

	x = map[0];
	y = map[1];
	if (y < 0 || y >= data->map_height)
		return (1);
	if (x < 0 || x >= data->map_width)
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

double	ray_length(t_camera *cam, t_vect *r)
{
	double	ax;
	double	ay;
	double	bx;
	double	by;

	ax = cam->cx;
	ay = cam->cy;
	bx = r->x;
	by = r->y;
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
