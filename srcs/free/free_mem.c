/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:05:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/26 13:21:04 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		join_threads(t_data *data);
void		destroy_locks(t_data *data);
void		file_error(char *path, int use_errno, char *msg);

static void	free_map(char **map)
{
	unsigned int	ind;

	ind = 0;
	while (map[ind] != NULL)
		free(map[ind++]);
	free(map);
	map = NULL;
}

void	free_vecs(t_parser *parser, int exit_fail, char *msg, char **map)
{
	if (msg != NULL)
		file_error(parser->file, FT, msg);
	if (map != NULL)
		free_map(map);
	vec_free(parser->textures_paths);
	free(parser->textures_paths);
	vec_free(parser->textures_info);
	free(parser->textures_info);
	vec_free(parser->floor);
	free(parser->floor);
	vec_free(parser->ceiling);
	free(parser->ceiling);
	vec_free(parser->map);
	free(parser->map);
	if (parser->line)
		free(parser->line);
	if (parser->next_line)
		free(parser->next_line);
	if (exit_fail == YES)
		exit(EXIT_FAILURE);
}

void	freeparser_exit(t_parser *parser)
{
	free(parser->textures_paths);
	parser->textures_paths = NULL;
	free(parser->textures_info);
	free(parser->map);
	free(parser->ceiling);
	free(parser->floor);
	exit(EXIT_FAILURE);
}

void	stop_game(t_data *data)
{
	pthread_mutex_lock(&data->layers_lock[STOP_FLG]);
	data->flag = STOP;
	pthread_mutex_unlock(&data->layers_lock[STOP_FLG]);
	join_threads(data);
	destroy_locks(data);
}


void	freedata_exit(t_data *data, int exit_status, int terminate_mlx,
		int premature)
{
	unsigned int	i;

	if (premature == NA)
		stop_game(data);
	if (data->parser)
		free_vecs(data->parser, NA, NULL, NULL);
	if (terminate_mlx == YES)
		mlx_terminate(data->mlx);
	i = 0;
	while ((int)i < data->tex_index)
	{
		if (data->texture->wall[i] != NULL)
			mlx_delete_texture(data->texture->wall[i]);
		i++;
	}
	vec_free(data->map_width);
	free(data->map_width);
	free_map(data->map);
	free(data->texture);
	free(data->rayinfo);
	exit(exit_status);
}
