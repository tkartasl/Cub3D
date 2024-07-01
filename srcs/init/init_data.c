/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:28:08 by username          #+#    #+#             */
/*   Updated: 2024/07/01 15:27:29 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_mlx(t_data *data);

void	extract_map_arr(t_parser *parser, t_data *data)
{
	int	x;
	int	y;
	char	**map;

	x = -1;
	y = -1;
	map = (char **)malloc(sizeof(char *) * (parser->map->len + 1));
	// TODO: malloc check
	while (++y < parser->map->len)
	{
		map[y] = *(char **)vec_get(parser->map, y);
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E')
			{
				data->camera_y = y * 64 + 32;
				data->camera_x = x * 64 + 32;
				data->playerdir = map[y][x];
			}
		}
	}
	map[y] = NULL;
	data->map_height = y;
	data->map = map;
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

t_textures	*init_texture(t_parser *parser, t_rayinfo **rayinfo)
{
	t_textures	*texture;

	texture = (t_textures *)malloc(sizeof(t_textures));
	if (texture == NULL)
	{
		free(*rayinfo);
		free_vecs(parser, YES, NA);
	}
	ft_memset(texture, 0, sizeof(t_textures));
	return (texture);
}

void	init_data_mlx(t_data *data, t_parser *parser)
{
	data->rayinfo = init_rayinfo(parser);
	//data->line = init_line(parser, &data->rayinfo);
	data->texture = init_texture(data->parser, &data->rayinfo);
	extract_map_arr(parser, data);
	data->parser = parser;
	if (data->playerdir == 'N')
		data->player_angle = NORTH;
	else if (data->playerdir == 'W')
		data->player_angle = WEST;
	else if (data->playerdir == 'S')
		data->player_angle = SOUTH;
	else
		data->player_angle = EAST;
	data->rayinfo->ray_angle = data->player_angle;
	data->playerdir_x = cos(data->player_angle) * 7.5;
	data->playerdir_y = sin(data->player_angle) * 7.5;
	init_mlx(data);
}
