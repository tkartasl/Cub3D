/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 11:01:45 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/26 13:25:28 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	load_north_south_textures(t_data *data, int dir)
{
	mlx_texture_t	*tex;

	if (dir == SO)
	{
		tex = mlx_load_png("textures/arrow_south_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, YES);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	else
	{
		tex = mlx_load_png("textures/arrow_north_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, YES);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	mlx_delete_texture(tex);
}

static void	load_east_west_textures(t_data *data, int dir)
{
	mlx_texture_t	*tex;

	if (dir == WE)
	{
		tex = mlx_load_png("textures/arrow_west_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, YES);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	else
	{
		tex = mlx_load_png("textures/arrow_east_small.png");
		if (tex == NULL)
			freedata_exit(data, EXIT_FAILURE, YES, YES);
		data->player = mlx_texture_to_image(data->mlx, tex);
	}
	mlx_delete_texture(tex);
}

void	get_arrow_textures(t_data *data, int dir)
{
	mlx_delete_image(data->mlx, data->player);
	if (dir < WE)
		load_north_south_textures(data, dir);
	else
		load_east_west_textures(data, dir);
}

static void	load_textures(t_parser *parser, t_data *data, int index,
		int text_info)
{
	t_vec	*tex_paths;
	char	*texpath;

	tex_paths = parser->textures_paths;
	texpath = *(char **)vec_get(tex_paths, index);
	data->texture->wall[text_info] = mlx_load_png(texpath);
	if (data->texture->wall[text_info] == NULL)
	{
		free(texpath);
		free_vecs(parser, NA, IVALTEX, NULL);
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	}
	free(texpath);
}

void	get_textures(t_data *data, t_parser *parser)
{
	int		ind;
	t_vec	*tex_info;

	ind = -1;
	tex_info = parser->textures_info;
	while (++ind < (int)tex_info->len)
	{
		data->tex_index = ind + 1;
		if (*(int *)vec_get(tex_info, ind) == NO)
			load_textures(parser, data, ind, NO);
		else if (*(int *)vec_get(tex_info, ind) == SO)
			load_textures(parser, data, ind, SO);
		else if (*(int *)vec_get(tex_info, ind) == EA)
			load_textures(parser, data, ind, EA);
		else if (*(int *)vec_get(tex_info, ind) == WE)
			load_textures(parser, data, ind, WE);
	}
}
