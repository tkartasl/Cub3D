/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:00 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/17 12:34:14 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	calculate_steps_v(t_data *data, double *ray_y, double *ray_x, int *i)
{
	int	py;
	int	px;

	px = data->camera_x;
	py = data->camera_y;
	data->rayinfo->ntan = -tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > NORTH && data->rayinfo->ray_angle < SOUTH)
	{
		*ray_x = (((int)px >> 6) << 6) - 0.0001;
		*ray_y = (px - *ray_x) * data->rayinfo->ntan + py;
		data->rayinfo->step_x = -64;
	}
	if (data->rayinfo->ray_angle < NORTH || data->rayinfo->ray_angle > SOUTH)
	{
		*ray_x = (((int)px >> 6) << 6) + 64;
		*ray_y = (px - *ray_x) * data->rayinfo->ntan + py;
		data->rayinfo->step_x = 64;
	}
	data->rayinfo->step_y = -data->rayinfo->step_x * data->rayinfo->ntan;
	if (data->rayinfo->ray_angle == 0 || data->rayinfo->ray_angle == WEST)
	{
		*ray_x = px;
		*ray_y = py;
		*i = MAX_VIEW_DIST;
	}
}

void	calculate_steps_h(t_data *data, double *ray_y, double *ray_x, int *i)
{
	int	py;
	int	px;

	px = data->camera_x;
	py = data->camera_y;
	data->rayinfo->atan = -1 / tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > WEST)
	{
		*ray_y = (((int)py >> 6) << 6) - 0.0001;
		*ray_x = (py - *ray_y) * data->rayinfo->atan + px;
		data->rayinfo->step_y = -64;
	}
	if (data->rayinfo->ray_angle < WEST)
	{
		*ray_y = (((int)py >> 6) << 6) + 64;
		*ray_x = (py - *ray_y) * data->rayinfo->atan + px;
		data->rayinfo->step_y = 64;
	}
	data->rayinfo->step_x = -data->rayinfo->step_y * data->rayinfo->atan;
	if (data->rayinfo->ray_angle == WEST || data->rayinfo->ray_angle == 0)
	{
		*ray_x = px;
		*ray_y = py;
		*i = MAX_VIEW_DIST;
	}
}

double	check_vertical_hit(t_data *data)
{
	int		i;
	double	dist_v;

	dist_v = 1000000;
	i = 0;
	calculate_steps_v(data, &data->rayinfo->ray_y, &data->rayinfo->ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->ray_x >> 6;		
		data->rayinfo->map_y = (int)data->rayinfo->ray_y >> 6;
		if (check_overflow(data) == 0
			&& data->map[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			dist_v = ray_length(data);
			i = MAX_VIEW_DIST;
		}
		else
		{
			data->rayinfo->ray_x += data->rayinfo->step_x;
			data->rayinfo->ray_y += data->rayinfo->step_y;
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
	calculate_steps_h(data, &data->rayinfo->ray_y, &data->rayinfo->ray_x, &i);
	while (i < MAX_VIEW_DIST)
	{
		data->rayinfo->map_x = (int)data->rayinfo->ray_x >> 6;				
		data->rayinfo->map_y = (int)data->rayinfo->ray_y >> 6;
		if (check_overflow(data) == 0
			&& data->map[data->rayinfo->map_y][data->rayinfo->map_x] == 1)
		{
			dist = ray_length(data);
			i = MAX_VIEW_DIST;
		}
		else
		{
			data->rayinfo->ray_x += data->rayinfo->step_x;
			data->rayinfo->ray_y += data->rayinfo->step_y;
			i += 1;
		}
	}
	return (dist);
}
