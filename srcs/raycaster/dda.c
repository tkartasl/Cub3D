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

static void	calc_steps_v(t_camera *cam, t_vect *rv, double *steps, int *i)
{
	double	ntan;

	ntan = -tan(rv->angle);
	if (rv->angle > NORTH && rv->angle < SOUTH)
	{
		rv->x = (((int)cam->cx / UNITSIZE) * UNITSIZE) - 0.0001;
		rv->y = (cam->cx - rv->x) * ntan + cam->cy;
		steps[0] = -UNITSIZE;
	}
	else if (rv->angle < NORTH || rv->angle > SOUTH)
	{
		rv->x = (((int)cam->cx / UNITSIZE) * UNITSIZE) + UNITSIZE;
		rv->y = (cam->cx - rv->x) * ntan + cam->cy;
		steps[0] = UNITSIZE;
	}
	else if (rv->angle == 0 || rv->angle == WEST)
	{
		rv->x = cam->cx;
		rv->y = cam->cy;
		*i = MAX_VIEW_DIST;
	}
	steps[1] = -steps[0] * ntan;
}

static void	calc_steps_h(t_camera *cam, t_vect *rh, double *steps, int *i)
{
	double	atan;

	atan = -1 / tan(rh->angle);
	if (rh->angle > WEST)
	{
		rh->y = (((int)cam->cy / UNITSIZE) * UNITSIZE) - 0.0001;
		rh->x = (cam->cy - rh->y) * atan + cam->cx;
		steps[1] = -UNITSIZE;
	}
	else if (rh->angle < WEST)
	{
		rh->y = (((int)cam->cy / UNITSIZE) * UNITSIZE) + UNITSIZE;
		rh->x = (cam->cy - rh->y) * atan + cam->cx;
		steps[1] = -UNITSIZE;
	}
	else if (rh->angle == WEST || rh->angle == 0)
	{
		rh->x = cam->cx;
		rh->y = cam->cy;
		*i = MAX_VIEW_DIST;
	}
	steps[0] = -steps[1] * atan;
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
		map[0] = (int)rv->x / UNITSIZE;
		map[1] = (int)rv->y / UNITSIZE;
		if (check_overflow(data, map) == 0 && data->map[map[1]][map[0]] == '1')
		{
			dist = ray_length(cam, rv);
			break ;
		}
		else
		{
			rv->x += steps[0];
			rv->y += steps[1];
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
	ft_putnbr(rh->x);
	write(1, "\n", 1);
	write(1, "\n", 1);
	calc_steps_h(cam, rh, steps, &i);
	ft_putnbr(rh->x);
	write(1, "\n", 1);
	while (i < MAX_VIEW_DIST)
	{
		map[0] = (int)rh->x / UNITSIZE;
		map[1] = (int)rh->y / UNITSIZE;
		if (check_overflow(data, map) == 0 && data->map[map[1]][map[0]] == '1')
		{
			dist = ray_length(cam, rh);
			break ;
		}
		else
		{
			rh->x += steps[0];
			rh->y += steps[1];
			i += 1;
		}
	}
	return (dist);
}
