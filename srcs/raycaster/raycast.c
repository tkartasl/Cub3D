/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/08 12:40:25 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	minimap(t_data *data);
void	get_textures(t_data *data);

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
	//printf("dist: %f\n", data->rayinfo->raydist);
	//printf("ray x: %f\nray y: %f\n", data->rayinfo->ray_x, data->rayinfo->ray_y);
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
		printf("angle: %f\n", data->rayinfo->ray_angle);
		calc_texels(data, x_pos);
		draw_walls(data, x_pos);
		x_pos++;
	}
}

void	raycaster(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		freedata_exit(data, EXIT_FAILURE, YES);
	if (data->player_angle == SOUTH - PI)
		get_arrow_textures(data, 0);
	else if (data->player_angle == NORTH + PI)
		get_arrow_textures(data, 1);
	else if (data->player_angle == WEST)
		get_arrow_textures(data, 2);
	else
		get_arrow_textures(data, 3);
	if (mlx_image_to_window(data->mlx, data->minimap, 10, 10) < 0)
		freedata_exit(data, EXIT_FAILURE, YES);
	if (mlx_image_to_window(data->mlx, data->player, 165, 165) < 0)
		freedata_exit(data, EXIT_FAILURE, YES);
	get_textures(data);
	cast_rays(data);
	minimap(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_hook, data);
	mlx_loop_hook(data->mlx, &movement, data);
	mlx_loop(data->mlx);
}
