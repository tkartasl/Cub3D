/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/26 13:24:57 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	check_vertical_hit(t_data *data, t_camera *cam);
double	check_horizontal_hit(t_data *data, t_camera *cam);

static void	calc_texels(t_data *data, t_camera *cam)
{
	double	correct_angle;
	int		t_size;

	t_size = data->texture->wall[data->texture->idx]->height;
	correct_angle = cam->angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->texture->ty_off = 0;
	data->rayinfo->raydist *= cos(correct_angle);
	data->texture->height = (UNITSIZE * HEIGHT) / data->rayinfo->raydist;
	data->texture->ty_step = t_size / (double)data->texture->height;
	get_texture_index(data, t_size);
	if (data->texture->height > HEIGHT)
	{
		data->texture->ty_off = (data->texture->height - HEIGHT) / 2;
		data->texture->height = HEIGHT;
	}
	data->texture->y = data->texture->ty_off * data->texture->ty_step;
}

static void	set_ray_values(t_data *data)
{
	if (data->rayinfo->dist_v >= data->rayinfo->dist_h)
	{
		data->texture->axis = 'x';
		data->rayinfo->raydist = data->rayinfo->dist_h;
		data->rayinfo->ray_x = data->rayinfo->h_ray_x;
		data->rayinfo->ray_y = data->rayinfo->h_ray_y;
	}
	else
	{
		data->texture->axis = 'y';
		data->rayinfo->raydist = data->rayinfo->dist_v;
		data->rayinfo->ray_x = data->rayinfo->v_ray_x;
		data->rayinfo->ray_y = data->rayinfo->v_ray_y;
	}
}

void	cast_rays(t_data *data, t_camera *cam)
{
	int	x;

	x = 0;
	data->rayinfo->ray_angle = cam->angle - DEGREE * FOV / 2;
	reset_ray_angle(&data->rayinfo->ray_angle);
	while (x < WIDTH)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data, cam);
		data->rayinfo->dist_v = check_vertical_hit(data, cam);
		set_ray_values(data);
		calc_texels(data, cam);
		draw_walls(data, x);
		x++;
	}
}

void	raycaster(t_data *data)
{
	t_camera	cam;

	get_camera(data, &cam);
	cast_rays(data, &cam);
}
