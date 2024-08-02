/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:00 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/22 15:02:07 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	step_v(t_data *data, double *ray_y, double *ray_x, t_camera *cam)
{
	double	ntan;

	ntan = -tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > NORTH && data->rayinfo->ray_angle < SOUTH)
	{
		*ray_x = (((int)cam->cx / UNITSIZE) * UNITSIZE) - 0.0001;
		*ray_y = (cam->cx - *ray_x) * ntan + cam->cy;
		data->rayinfo->step_x = -UNITSIZE;
	}
	else if (data->rayinfo->ray_angle < NORTH
		|| data->rayinfo->ray_angle > SOUTH)
	{
		*ray_x = (((int)cam->cx / UNITSIZE) * UNITSIZE) + UNITSIZE;
		*ray_y = (cam->cx - *ray_x) * ntan + cam->cy;
		data->rayinfo->step_x = UNITSIZE;
	}
	else if (data->rayinfo->ray_angle == 0 || data->rayinfo->ray_angle == WEST)
	{
		*ray_x = cam->cx;
		*ray_y = cam->cy;
		return (MAX_VIEW_DIST);
	}
	data->rayinfo->step_y = -data->rayinfo->step_x * ntan;
	return (0);
}

static int	step_h(t_data *data, double *ray_y, double *ray_x, t_camera *cam)
{
	double	atan;

	atan = -1 / tan(data->rayinfo->ray_angle);
	if (data->rayinfo->ray_angle > WEST)
	{
		*ray_y = (((int)cam->cy / UNITSIZE) * UNITSIZE) - 0.0001;
		*ray_x = (cam->cy - *ray_y) * atan + cam->cx;
		data->rayinfo->step_y = -UNITSIZE;
	}
	else if (data->rayinfo->ray_angle < WEST)
	{
		*ray_y = (((int)cam->cy / UNITSIZE) * UNITSIZE) + UNITSIZE;
		*ray_x = (cam->cy - *ray_y) * atan + cam->cx;
		data->rayinfo->step_y = UNITSIZE;
	}
	else if (data->rayinfo->ray_angle == WEST || data->rayinfo->ray_angle == 0)
	{
		*ray_x = cam->cx;
		*ray_y = cam->cy;
		return (MAX_VIEW_DIST);
	}
	data->rayinfo->step_x = -data->rayinfo->step_y * atan;
	return (0);
}

double	check_vertical_hit(t_data *data, t_camera *cam)
{
	int		i;
	double	dist_v;

	dist_v = 1000000;
	i = step_v(data, &data->rayinfo->v_ray_y, &data->rayinfo->v_ray_x, cam);
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

double	check_horizontal_hit(t_data *data, t_camera *cam)
{
	int		i;
	double	dist;

	dist = 1000000;
	i = step_h(data, &data->rayinfo->h_ray_y, &data->rayinfo->h_ray_x, cam);
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
