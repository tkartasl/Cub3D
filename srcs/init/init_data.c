/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:28:08 by username          #+#    #+#             */
/*   Updated: 2024/07/08 12:51:40 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_mlx(t_data *data);

void	load_textures(t_data *data, int index, int text_info)
{
	t_vec	*tex_paths;

	tex_paths = data->parser->textures_paths;
	data->texture->wall[text_info] = mlx_load_png(*(char **)vec_get(tex_paths, index));
	if (data->texture->wall[text_info] == NULL)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
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

char	extract_map_arr(t_parser *parser, t_data *data)
{
	int	x;
	int	y;
	char	**map;
	char	playerdir;

	x = -1;
	y = -1;
	data->map_width = 0;
	map = (char **)malloc(sizeof(char *) * (parser->map->len + 1));
	if (map == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	while (++y < parser->map->len)
	{
		map[y] = *(char **)vec_get(parser->map, y);
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E')
			{
				data->camera_y = y * UNITSIZE + UNITSIZE/2;
				data->camera_x = x * UNITSIZE + UNITSIZE/2;
				playerdir = map[y][x];
			}
		}
		if (data->map_width < x)
			data->map_width = x;
	}
	map[y] = NULL;
	data->map_height = y;
	data->map = map;
	return (playerdir);
}

t_rayinfo	*init_rayinfo(t_parser *parser)
{
	t_rayinfo	*rayinfo;

	rayinfo = (t_rayinfo *)malloc(sizeof(t_rayinfo));
	if (rayinfo == NULL)
		free_vecs(parser, YES, NA);
	ft_memset(rayinfo, 0, sizeof(t_rayinfo));
	return (rayinfo);
}

void	init_texture(t_data *data)
{
	t_textures	*texture;

	texture = (t_textures *)malloc(sizeof(t_textures));
	if (texture == NULL)
	{
		free(data->rayinfo);
		free_vecs(data->parser, YES, NA);
	}
	ft_memset(texture, 0, sizeof(t_textures));
	get_textures(data);
}

void	init_data_mlx(t_data *data, t_parser *parser)
{
	char	playerdir;

	data->parser = parser;
	data->flag = CONTINUE;
	data->rayinfo = init_rayinfo(parser);
	init_texture(data);
	playerdir = extract_map_arr(parser, data);
	if (playerdir == 'N')
		data->player_angle = NORTH + PI;
	else if (playerdir == 'W')
		data->player_angle = WEST;
	else if (playerdir == 'S')
		data->player_angle = SOUTH - PI;
	else
		data->player_angle = EAST;
	data->rayinfo->ray_angle = data->player_angle;
	data->playerdir_x = cos(data->player_angle) * 7.5;
	data->playerdir_y = sin(data->player_angle) * 7.5;
	init_mlx(data);
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
	if (mlx_image_to_window(data->mlx, data->minimap, 15, 15) < 0)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
}
