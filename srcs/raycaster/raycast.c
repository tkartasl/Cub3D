/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/01 14:59:02 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	minimap(t_data *data);

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

double	fps(void)
{
	return (mlx_get_time());
}

static void	calc_texels(t_data *data, int x_pos)
{
	double	correct_angle;
	int		t_size;

	t_size = data->texture->wall[0]->height;
	correct_angle = data->player_angle - data->rayinfo->ray_angle;
	reset_ray_angle(&correct_angle);
	data->texture->ty_off = 0;
	data->rayinfo->raydist *= cos(correct_angle);
	data->texture->height = (UNITSIZE * HEIGHT) / data->rayinfo->raydist;
	data->texture->ty_step = t_size / (double)data->texture->height;
	get_texture_index(data, x_pos, t_size);
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

void	cast_rays(t_data *data)
{
	int	x_pos;

	x_pos = 0;
	data->rayinfo->ray_angle = data->player_angle - DEGREE * FOV / 2;
	reset_ray_angle(&data->rayinfo->ray_angle);
	while (x_pos < WIDTH)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data);
		data->rayinfo->dist_v = check_vertical_hit(data);
		set_ray_values(data);
		calc_texels(data, x_pos);
		draw_walls(data, x_pos);
		x_pos++;
	}
}

void	load_textures(t_data *data, int index, int text_info)
{
	t_vec	*tex_paths;

	tex_paths = data->parser->textures_paths;
	data->texture->wall[text_info] = mlx_load_png(*(char **)vec_get(tex_paths, index));
	if (data->texture->wall[text_info] == NULL)
		freedata_exit(data, EXIT_FAILURE, YES);
}

void	get_textures(t_data *data)
{
	int		ind;
	t_vec	*tex_info;

	ind = -1;
	tex_info = data->parser->textures_info;
	while (++ind < tex_info->len)
	{
		if (*(int *)vec_get(tex_info, ind) == NO)
			load_textures(data, ind, NO);
		else if (*(int *)vec_get(tex_info, ind) == SO)
			load_textures(data, ind, SO);
		else if (*(int *)vec_get(tex_info, ind) == EA)
			load_textures(data, ind, EA);
		else if (*(int *)vec_get(tex_info, ind) == WE)
			load_textures(data, ind, WE);
	}
}

void	raycaster(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		error();
	if (mlx_image_to_window(data->mlx, data->minimap, 15, 15) < 0)
		error();
	get_textures(data);
	cast_rays(data);
	minimap(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_hook, data);
	mlx_loop_hook(data->mlx, &movement, data);
	mlx_loop(data->mlx);
}
