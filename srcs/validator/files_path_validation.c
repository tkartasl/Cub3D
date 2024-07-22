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

# include "cub3D.h"

static int	open_file(t_parser *parser, char *map_path, int file)
{
	int	fd;

	fd = -2;
	fd = open(map_path, O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		if (file == MAP)
			free_vecs(parser, YES, MDPATH, NULL);
		free_vecs(parser, YES, TDPATH, NULL);
	}
	fd = open(map_path, O_RDONLY);
	if (fd == -1)
	{
		if (file == MAP)
			free_vecs(parser, YES, MWRPATH, NULL);
		free_vecs(parser, YES, TWRPATH, NULL);
	}
	return (fd);
}

int	open_validate_file(t_parser *parser, char *map_path, char *ext, int texture_path)
{
	size_t	path_len;
	size_t	bfr_ext;
	int		fd;
	char	*msg;
	int	file;

	msg = TWRPATH;
	file = TEXTURE;
	if (!ft_strncmp(ext, ".cub", 4))
	{
		file = MAP;
		msg = MWRPATH;
	}
	if (map_path[0] == '.')
		free_vecs(parser, YES, msg, NULL);
	path_len = ft_strlen(map_path);
	bfr_ext = path_len - 4;
	if (ft_strncmp(ext, &map_path[bfr_ext], path_len - bfr_ext))
		free_vecs(parser, YES, msg, NULL);
	fd = open_file(parser, map_path, file);
	if (texture_path == YES)
	{
		close(fd);
		fd = 1;
	}
	return (fd);
}
