/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 14:28:08 by username          #+#    #+#             */
/*   Updated: 2024/07/26 13:18:41 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_mlx(t_data *data);
void	get_textures(t_data *data, t_parser *parser);
void	get_colors(t_parser *parser, t_data *data);
void	check_mapholes(t_parser *parser, t_data *data);

void	find_player(t_data *data, char **map, unsigned int y, char *playerdir)
{
	unsigned int	x;

	x = 0;
	while (map[y][x])
	{
		if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'W'
			|| map[y][x] == 'E')
		{
			data->camera_y = y * UNITSIZE + UNITSIZE / 2;
			data->camera_x = x * UNITSIZE + UNITSIZE / 2;
			*playerdir = map[y][x];
		}
		++x;
	}
	if (vec_push(data->map_width, &x) == 0)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
}

char	extract_map_arr(t_parser *parser, t_data *data)
{
	unsigned int	y;
	char			**map;
	char			playerdir;

	y = 0;
	vec_new(data->map_width, 0, sizeof(int));
	map = (char **)malloc(sizeof(char *) * (parser->map->len + 1));
	if (map == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	while (y < parser->map->len)
	{
		map[y] = *(char **)vec_get(parser->map, y);
		find_player(data, map, y, &playerdir);
		++y;
	}
	map[y] = NULL;
	data->map_height = y;
	data->map = map;
	check_mapholes(parser, data);
	return (playerdir);
}

static	t_rayinfo	*init_rayinfo(t_data *data)
{
	t_rayinfo	*rayinfo;

	rayinfo = (t_rayinfo *)malloc(sizeof(t_rayinfo));
	if (rayinfo == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	ft_memset(rayinfo, 0, sizeof(t_rayinfo));
	return (rayinfo);
}

static	void	init_texture(t_data *data, t_parser *parser)
{
	t_textures	*texture;

	texture = (t_textures *)malloc(sizeof(t_textures));
	if (texture == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	ft_memset(texture, 0, sizeof(t_textures));
	data->texture = texture;
	get_textures(data, parser);
}

void	init_data_mlx(t_data *data, t_parser *parser)
{
	char	playerdir;

	data->parser = parser;
	data->map_width = (t_vec *)malloc(sizeof(t_vec));
	if (data->map_width == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	playerdir = extract_map_arr(parser, data);
	data->flag = CONTINUE;
	data->rayinfo = init_rayinfo(data);
	init_texture(data, parser);
	get_colors(parser, data);
	if (playerdir == 'N')
		data->player_angle = NORTH + PI;
	else if (playerdir == 'W')
		data->player_angle = WEST;
	else if (playerdir == 'S')
		data->player_angle = SOUTH - PI;
	else
		data->player_angle = EAST;
	data->rayinfo->ray_angle = data->player_angle;
	data->playerdir_x = cos(data->player_angle) * MOVE_SPEED;
	data->playerdir_y = sin(data->player_angle) * MOVE_SPEED;
	init_mlx(data);
	free_vecs(parser, NA, NULL, NULL);
	data->parser = NULL;
}
