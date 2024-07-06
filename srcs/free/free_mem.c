/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:05:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/01 15:19:22 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	join_threads(t_data *data);
void	destroy_locks(t_data *data);

void	file_error(char *path, int use_errno)
{
	if (use_errno == YES)
	{
		ft_putstr_fd("cub3d: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd("", 2);
	}
	ft_putstr_fd("cub3d: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": is not valid map file", 2);
	exit(EXIT_FAILURE);
}

static	void	free_lines(t_parser *parser, int lines)
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

void	print_vecs(t_parser *parser)
{
	int	ind;

	printf("textures_paths len: %d\n", parser->textures_paths->len);
	ind = -1;
	while (++ind < parser->textures_paths->len)
		printf("path: %s\n", *(char **)vec_get(parser->textures_paths, ind));
	printf("floor len: %zu\n", parser->floor->len);
	ind = -1;
	if (parser->floor->len > 0)
	{
		while (++ind < parser->floor->len)
			printf("floor color: %d\n", *(int **)vec_get(parser->floor, ind));
	}
	printf("ceiling len: %zu\n", parser->ceiling->len);
	ind = -1;
	if (parser->ceiling->len > 0)
	{
		while (++ind < parser->ceiling->len)
			printf("ceiling color: %d\n", *(int **)vec_get(parser->ceiling, ind));
	}
	printf("map len: %zu\n", parser->map->len);
	ind = -1;
	if (parser->map->len > 0)
	{
		while (++ind < parser->map->len)
			printf("map line: %s\n", *(char **)vec_get(parser->map, ind));
	}
}

void	free_vecs(t_parser *parser, int exit_fail, int print_err)
{
	// TODO: ALSO free what these vecs hold

	print_vecs(parser);
	if (print_err == YES)
		file_error(parser->file, 42);
	if (parser->line != NULL && *parser->line != NULL)
		free(*parser->line);
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
	if (parser->map && parser->map->len)
		free_lines(parser, MAP);
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
	mlx_close_window(data->mlx);
}

void	freedata_exit(t_data *data, int exit_status, int terminate_mlx, int premature)
{
	int	i;

	if (premature == NA)
		stop_game(data);
	if (terminate_mlx == YES)
		mlx_terminate(data->mlx);
	free_vecs(data->parser, NA, NA);
	i = -1;
	while (++i < 4)
		free(data->texture->wall[i]);
	free(data->texture);
	exit(exit_status);
}
