/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:01:45 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/08 13:35:58 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

static void	load_north_south_textures(t_data *data, int dir)
{
	mlx_texture_t	*tex;

	if (dir == 0)
	{
		tex = mlx_load_png("textures/arrow_south_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	else
	{
		tex = mlx_load_png("textures/arrow_north_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	mlx_delete_texture(tex);
}

static void	load_east_west_textures(t_data *data, int dir)
{
	mlx_texture_t	*tex;

	if (dir == 2)
	{
		tex = mlx_load_png("textures/arrow_west_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	else
	{
		tex = mlx_load_png("textures/arrow_east_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	mlx_delete_texture(tex);
}

void	get_arrow_textures(t_data *data, int dir)
{
	data->player = mlx_new_image(data->mlx, 12, 12);
	if (!data->player)
		freedata_exit(data, EXIT_FAILURE, YES, NA);
	data->minimap = mlx_new_image(data->mlx, 320, 320);
	if (!data->minimap)
		freedata_exit(data, EXIT_FAILURE, YES, NA);
	if (dir < 2)
		load_north_south_textures(data, dir);
	else
		load_east_west_textures(data, dir);
}

static void	load_textures(t_data *data, int index, int text_info)
{
	t_vec	*tex_paths;
	char	*p;
	mlx_texture_t	*t;

	tex_paths = data->parser->textures_paths;
	data->texture->wall[text_info] = mlx_load_png(*(char **) \
		vec_get(tex_paths, index));
	if (data->texture->wall[text_info] == NULL)
		freedata_exit(data, EXIT_FAILURE, YES, NA);
}

void	get_textures(t_data *data)
{
	int				ind;
	t_vec			*tex_info;

	ind = -1;
	tex_info = data->parser->textures_info;
	while (++ind < tex_info->len)
	{
		if (*(int *)vec_get(tex_info, ind) == SO)
			load_textures(data, ind, NO);
		else if (*(int *)vec_get(tex_info, ind) == NO)
			load_textures(data, ind, SO);
		else if (*(int *)vec_get(tex_info, ind) == WE)
			load_textures(data, ind, EA);
		else if (*(int *)vec_get(tex_info, ind) == EA)
			load_textures(data, ind, WE);
	}
}