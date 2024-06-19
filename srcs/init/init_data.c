/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:28:08 by username          #+#    #+#             */
/*   Updated: 2024/06/19 13:45:51 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
				data->camera_y = (y * 64) + 32;
				data->camera_x = (x * 64) + 32;
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

t_line	*init_line(t_parser *parser, t_rayinfo **rayinfo)
{
	t_line		*line;

	line = (t_line *)malloc(sizeof(t_line));
	if (line == NULL)
	{
		free(*rayinfo);
		free_vecs(parser, YES, NA);
	}
	ft_memset(line, 0, sizeof(t_line));
	return (line);
}

t_textures	*init_texture(t_parser *parser, t_rayinfo **rayinfo, t_line **line)
{
	t_textures	*texture;

	texture = (t_textures *)malloc(sizeof(t_textures));
	if (texture == NULL)
	{
		free(*rayinfo);
		free(*line);
		free_vecs(parser, YES, NA);
	}
	ft_memset(texture, 0, sizeof(t_textures));
	return (texture);
}

void	init_data_mlx(t_data *data, t_parser *parser)
{
	data->rayinfo = init_rayinfo(parser);
	data->line = init_line(parser, &data->rayinfo);
	data->texture = init_texture(data->parser, &data->rayinfo, &data->line);
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
	data->playerdir_x = cos(data->player_angle) * 10;
	data->playerdir_y = sin(data->player_angle) * 10;
	data->map_width = 25;
	data->map_size = 50;
	init_mlx(data);
}
