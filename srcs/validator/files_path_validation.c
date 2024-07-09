/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_path_validation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:26:17 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/17 10:42:16 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	open_file(t_parser *parser, char *map_path)
{
	int	fd;

	fd = -2;
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		free_vecs(parser, YES, YES);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
		free_vecs(parser, YES, YES);
	return (fd);
}

int	open_validate_file(t_parser *parser, char *map_path, char *ext,
		int texture_path)
{
	size_t	path_len;
	size_t	bfr_ext;
	int		fd;

	path_len = ft_strlen(map_path);
	bfr_ext = path_len - 4;
	if (ft_strncmp(ext, &map_path[bfr_ext], path_len - bfr_ext))
		free_vecs(parser, YES, YES);
	fd = open_file(parser, map_path);
	if (texture_path == YES)
	{
		close(fd);
		fd = 1;
	}
	return (fd);
}
