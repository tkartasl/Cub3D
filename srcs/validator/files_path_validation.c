/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_path_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:26:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/23 10:19:32 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	open_file(t_parser *parser, char *path, int file)
{
	int	fd;

	fd = -2;
	fd = open(path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		if (file == MAP)
			free_vecs(parser, YES, MDPATH, NULL);
		free_vecs(parser, YES, TDPATH, NULL);
	}
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		if (file == MAP)
			free_vecs(parser, YES, MWRPATH, NULL);
		free_vecs(parser, YES, TWRPATH, NULL);
	}
	return (fd);
}

static	void	check_hidden_file(t_parser *parser, char *path, int file)
{
	size_t	len;

	len = ft_strlen(path);
	if (path[0] == '.' || (len > 4 && path[len - 5] == '/'))
	{
		if (file == MAP)
			free_vecs(parser, YES, MWRPATH, NULL);
		free_vecs(parser, YES, TWRPATH, NULL);
	}
}

int	open_validate_file(t_parser *parser, char *map_path, char *ext,
	int texture_path)
{
	size_t	path_len;
	size_t	bfr_ext;
	int		fd;
	int		file;

	file = TEXTURE;
	if (!ft_strncmp(ext, ".cub", 4))
		file = MAP;
	check_hidden_file(parser, map_path, file);
	path_len = ft_strlen(map_path);
	bfr_ext = path_len - 4;
	if (ft_strncmp(ext, &map_path[bfr_ext], path_len - bfr_ext))
	{
		if (file == MAP)
			free_vecs(parser, YES, MWRPATH, NULL);
		free_vecs(parser, YES, TWRPATH, NULL);
	}
	fd = open_file(parser, map_path, file);
	if (texture_path == YES)
	{
		close(fd);
		fd = 1;
	}
	return (fd);
}
