/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:05:43 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/17 10:41:50 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"


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

static	void	free_lines(t_cub *cub, int lines)
{
	int	ind;

	ind = -1;
	if (lines == TEXTURE)
	{
		while (++ind < cub->textures_paths->len)
			free(*(char **)vec_get(cub->textures_paths, ind));
	}
	else if (lines == MAP)
	{
		while (++ind < cub->map->len)
			free(*(char **)vec_get(cub->map, ind));
	}
}

void	print_vecs(t_cub *cub)
{
	int	ind;

	printf("textures_paths len: %d\n", cub->textures_paths->len);
	ind = -1;
	while (++ind < cub->textures_paths->len)
		printf("path: %s\n", *(char **)vec_get(cub->textures_paths, ind));
	printf("floor len: %zu\n", cub->floor->len);
	ind = -1;
	if (cub->floor->len > 0)
	{
		while (++ind < cub->floor->len)
			printf("floor color: %d\n", *(int **)vec_get(cub->floor, ind));
	}
	printf("ceiling len: %zu\n", cub->ceiling->len);
	ind = -1;
	if (cub->ceiling->len > 0)
	{
		while (++ind < cub->ceiling->len)
			printf("ceiling color: %d\n", *(int **)vec_get(cub->ceiling, ind));
	}
	printf("map len: %zu\n", cub->map->len);
	ind = -1;
	if (cub->map->len > 0)
	{
		while (++ind < cub->map->len)
			printf("map line: %s\n", *(char **)vec_get(cub->map, ind));
	}
}

void	free_vecs(t_cub *cub, int exit_fail, int print_err)
{
	// TODO: ALSO free what these vecs hold

	print_vecs(cub);
	if (print_err == YES)
		file_error(cub->file, 42);
	if (cub->line != NULL && *cub->line != NULL)
		free(*cub->line);
	if (cub->textures_paths && cub->textures_paths->len)
		free_lines(cub, TEXTURE);
	vec_free(cub->textures_paths);
	free(cub->textures_paths);
	vec_free(cub->textures_info);
	free(cub->textures_info);
	vec_free(cub->floor);
	free(cub->floor);
	vec_free(cub->ceiling);
	free(cub->ceiling);
	if (cub->map && cub->map->len)
		free_lines(cub, MAP);
	vec_free(cub->map);
	free(cub->map);
	if (exit_fail == YES)
		exit(EXIT_FAILURE);
}

void	freecub_exit(t_cub *cub)
{
	free(cub->textures_paths);
	free(cub->textures_info);
	free(cub->map);
	free(cub->ceiling);
	free(cub->floor);
	exit(EXIT_FAILURE);
}


