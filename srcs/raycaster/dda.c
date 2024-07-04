/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:00 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/01 15:14:54 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	calc_steps_v(t_data *data, double *ray_y, double *ray_x, int *i)
{
	double	ntan;

	ntan = -tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > NORTH && data->rayinfo->ray_angle < SOUTH)
	{
		*ray_x = (((int)data->camera_x / UNITSIZE) * UNITSIZE) - 0.0001;
		*ray_y = (data->camera_x - *ray_x) * ntan + data->camera_y;
		data->rayinfo->step_x = -UNITSIZE;
	}
	else if (data->rayinfo->ray_angle < NORTH
		|| data->rayinfo->ray_angle > SOUTH)
	{
		*ray_x = (((int)data->camera_x / UNITSIZE) * UNITSIZE) + UNITSIZE;
		*ray_y = (data->camera_x - *ray_x) * ntan + data->camera_y;
		data->rayinfo->step_x = UNITSIZE;
	}
	else if (data->rayinfo->ray_angle == 0 || data->rayinfo->ray_angle == WEST)
	{
		*ray_x = data->camera_x;
		*ray_y = data->camera_y;
		*i = MAX_VIEW_DIST;
	}
	data->rayinfo->step_y = -data->rayinfo->step_x * ntan;
}

static void	calc_steps_h(t_data *data, double *ray_y, double *ray_x, int *i)
{
	double	atan;

	atan = -1 / tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > WEST)
	{
		*ray_y = (((int)data->camera_y / UNITSIZE) * UNITSIZE) - 0.0001;
		*ray_x = (data->camera_y - *ray_y) * atan + data->camera_x;
		data->rayinfo->step_y = -UNITSIZE;
	}
	else if (data->rayinfo->ray_angle < WEST)
	{
		*ray_y = (((int)data->camera_y / UNITSIZE) * UNITSIZE) + UNITSIZE;
		*ray_x = (data->camera_y - *ray_y) * atan + data->camera_x;
		data->rayinfo->step_y = UNITSIZE;
	}
	else if (data->rayinfo->ray_angle == WEST || data->rayinfo->ray_angle == 0)
	{
		*ray_x = data->camera_x;
		*ray_y = data->camera_y;
		*i = MAX_VIEW_DIST;
	}
	data->rayinfo->step_x = -data->rayinfo->step_y * atan;
}

double	check_vertical_hit(t_data *data)
{
	int		i;
	double	dist_v;

	dist_v = 1000000;
	i = 0;
	calc_steps_v(data, &data->rayinfo->v_ray_y, &data->rayinfo->v_ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->v_ray_x / UNITSIZE;
		data->rayinfo->map_y = (int)data->rayinfo->v_ray_y / UNITSIZE;
		if (check_overflow(data) == 0
			&& data->map[data->rayinfo->map_y][data->rayinfo->map_x] == '1')
		{
			dist_v = ray_length(data, 0);
			break ;
		}
		else
		{
			data->rayinfo->v_ray_x += data->rayinfo->step_x;
			data->rayinfo->v_ray_y += data->rayinfo->step_y;
			i += 1;
			}
	}
	return (dist_v);
}

double	check_horizontal_hit(t_data *data)
{
	int		i;
	double	dist;

	dist = 1000000;
	i = 0;
	calc_steps_h(data, &data->rayinfo->h_ray_y, &data->rayinfo->h_ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->h_ray_x / UNITSIZE;
		data->rayinfo->map_y = (int)data->rayinfo->h_ray_y / UNITSIZE;
		if (check_overflow(data) == 0
			&& data->map[data->rayinfo->map_y][data->rayinfo->map_x] == '1')
		{
			dist = ray_length(data, 1);
			break ;
		}
		else
		{
			data->rayinfo->h_ray_x += data->rayinfo->step_x;
			data->rayinfo->h_ray_y += data->rayinfo->step_y;
			i += 1;
		}
	}
	return (dist);
}
