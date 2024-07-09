/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:05:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/09 14:47:48 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void		join_threads(t_data *data);
void		destroy_locks(t_data *data);
void		file_error(char *path, int use_errno);

static void	free_lines(t_parser *parser, int lines)
{
	int	ind;

	ind = -1;
	if (lines == TEXTURE)
	{
		while (++ind < parser->textures_paths->len)
			free(*(char **)vec_get(parser->textures_paths, ind));
	}
	else if (lines == MAP)
	{
		while (++ind < parser->map->len)
			free(*(char **)vec_get(parser->map, ind));
	}
}

void	free_vecs(t_parser *parser, int exit_fail, int print_err)
{
	if (print_err == YES)
		file_error(parser->file, 42);
	if (parser->textures_paths && parser->textures_paths->len)
		free_lines(parser, TEXTURE);
	vec_free(parser->textures_paths);
	free(parser->textures_paths);
	vec_free(parser->textures_info);
	free(parser->textures_info);
	vec_free(parser->floor);
	free(parser->floor);
	vec_free(parser->ceiling);
	free(parser->ceiling);
	// if (parser->map && parser->map->len)
	// 	free_lines(parser, MAP);
	vec_free(parser->map);
	free(parser->map);
	if (exit_fail == YES)
		exit(EXIT_FAILURE);
}

void	freeparser_exit(t_parser *parser)
{
	free(parser->textures_paths);
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
	int	i;

	if (premature == NA)
		stop_game(data);
	if (terminate_mlx == YES)
		mlx_terminate(data->mlx);
	i = -1;
	while (++i < 4)
		mlx_delete_texture(data->texture->wall[i]);
	free(data->texture);
	free(data->rayinfo);
	exit(exit_status);
}
