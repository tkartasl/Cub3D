/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 10:03:00 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/06 00:14:19 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void	calc_steps_v(t_camera *cam, t_vect *rv, double *steps, int *i)
{
	double	ntan;

	ntan = -tan(rv->angle);
	if (rv->angle > NORTH && rv->angle < SOUTH)
	{
		rv->x = (((int)cam->cx / UNITSIZE) * UNITSIZE) - 0.0001;
		rv->y = (cam->cx - rv->x) * ntan + cam->cy;
		steps[X] = -UNITSIZE;
	}
	else if (rv->angle < NORTH || rv->angle > SOUTH)
	{
		rv->x = (((int)cam->cx / UNITSIZE) * UNITSIZE) + UNITSIZE;
		rv->y = (cam->cx - rv->x) * ntan + cam->cy;
		steps[X] = UNITSIZE;
	}
	else if (rv->angle == 0 || rv->angle == WEST)
	{
		rv->x = cam->cx;
		rv->y = cam->cy;
		*i = MAX_VIEW_DIST;
	}
	steps[Y] = -steps[X] * ntan;
}

static void	calc_steps_h(t_camera *cam, t_vect *rh, double *steps, int *i)
{
	double	atan;

	atan = -1 / tan(rh->angle);
	if (rh->angle > WEST)
	{
		rh->y = (((int)cam->cy / UNITSIZE) * UNITSIZE) - 0.0001;
		rh->x = (cam->cy - rh->y) * atan + cam->cx;
		steps[Y] = -UNITSIZE;
	}
	else if (rh->angle < WEST)
	{
		rh->y = (((int)cam->cy / UNITSIZE) * UNITSIZE) + UNITSIZE;
		rh->x = (cam->cy - rh->y) * atan + cam->cx;
		steps[Y] = -UNITSIZE;
	}
	else if (rh->angle == WEST || rh->angle == 0)
	{
		rh->x = cam->cx;
		rh->y = cam->cy;
		*i = MAX_VIEW_DIST;
	}
	steps[X] = -steps[Y] * atan;
}

double	check_vertical_hit(t_data *data, t_camera *cam, t_vect *rv)
{
	int		i;
	double	dist;
	int	map[2];
	double	steps[2];

	dist = 1000000;
	i = 0;
	calc_steps_v(cam, rv, steps, &i);
	while (i < MAX_VIEW_DIST)
	{
		map[X] = (int)rv->x / UNITSIZE;
		map[Y] = (int)rv->y / UNITSIZE;
		if (check_overflow(data, map) == 0 && data->map[map[Y]][map[X]] == '1')
		{
			dist = ray_length(cam, rv);
			break ;
		}
		else
		{
			rv->x += steps[X];
			rv->y += steps[Y];
			i += 1;
			}
	}
	return (dist);
}

double	check_horizontal_hit(t_data *data, t_camera *cam, t_vect *rh)
{
	int		i;
	double	dist;
	int	map[2];
	double	steps[2];

	dist = 1000000;
	i = 0;
	calc_steps_h(cam, rh, steps, &i);
	while (i < MAX_VIEW_DIST)
	{
		map[X] = (int)rh->x / UNITSIZE;
		map[Y] = (int)rh->y / UNITSIZE;
		if (check_overflow(data, map) == 0 && data->map[map[Y]][map[X]] == '1')
		{
			dist = ray_length(cam, rh);
			break ;
		}
		else
		{
			rh->x += steps[X];
			rh->y += steps[Y];
			i += 1;
		}
	}
	return (dist);
}
