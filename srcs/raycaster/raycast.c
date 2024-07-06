/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/06 00:20:05 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	fps(void)
{
	return (mlx_get_time());
}

static void	calc_texels(t_data *data, t_camera *cam, int x, t_vect *r)
{
	double	correct_angle;
	int		t_size;

	t_size = data->texture->wall[0]->height;
	correct_angle = cam->angle - r->angle;
	reset_ray_angle(&correct_angle);
	data->texture->ty_off = 0;
	r->dist *= cos(correct_angle);
	data->texture->height = (UNITSIZE * HEIGHT) / r->dist;
	data->texture->ty_step = t_size / (double)data->texture->height;
	get_texture_index(data, x, t_size, r);
	if (data->texture->height > HEIGHT)
	{
		data->texture->ty_off = (data->texture->height - HEIGHT) / 2;
		data->texture->height = HEIGHT;
	}
	data->texture->y = data->texture->ty_off * data->texture->ty_step;
}

static void	set_ray_values(t_vect *r, t_vect *rh, t_vect *rv)
{
	if (rv->dist >= rh->dist)
	{
		r->axis = 'x';
		r->dist = rh->dist;
		r->x = rh->x;
		r->y = rh->y;
	}
	else
	{
		r->axis = 'y';
		r->dist = rv->dist;
		r->x = rv->x;
		r->y = rv->y;
	}
	rh->angle = r->angle;
	rv->angle = r->angle;
}

void	init_ray(t_vect *ray, t_camera *cam)
{
	ray->x = 0;
	ray->y = 0;
	ray->dist = 0.0;
	ray->axis = 0;
	ray->angle = cam->angle - DEGREE * FOV / 2;
	reset_ray_angle(&ray->angle);
}

void	cast_rays(t_data *data, t_camera *cam, t_vect *r)
{
	int	x;
	t_vect	rh;
	t_vect	rv;

	init_ray(&rh, cam);
	init_ray(&rv, cam);
	while (x < WIDTH)
	{
		rh.dist = check_horizontal_hit(data, cam, &rh);
		rv.dist = check_vertical_hit(data, cam, &rv);
		set_ray_values(r, &rh, &rv);
		calc_texels(data, cam, x, r);
		draw_walls(data, x, r);
		x++;
	}
}

void	*raycaster(void *arg)
{
	t_data	*data;
	t_camera	cam;
	t_vect		r;

	data = (t_data *)arg;
	while (game_continues(data))
	{
		get_camera(data, &cam);
		init_ray(&r, &cam);
		cast_rays(data, &cam, &r);
	}
	return (NULL);
}
