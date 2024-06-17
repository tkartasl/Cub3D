/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_begins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:20 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:22 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_until_map(t_cub *cub, int fd);
void	parse_map(t_cub *cub, int fd);

void	free_exit(t_cub *cub, char **type_id, int print_err)
{
	free(*type_id);
	free_vecs(cub, YES, print_err);
}

void	next_strings_end(char *line, int *end, int check_comma)
{
	char	c;

	c = line[*end];
	while (c && !ft_isspace(c))
	{
		if (check_comma && c == ',')
			break ;
		++(*end);
		c = line[*end];
	}
}

void	skip_spaces(char *s, int *ind)
{
	while (s[*ind] != '\0' && ft_isspace(s[*ind]))
		++(*ind);
}

void	eof_malloc_check(t_cub *cub, int malloc_flag, int map, int fd)
{
	// TODO: take this function where gnl is called
	if (*cub->line == NULL && malloc_flag == 1)
	{
		close(fd);
		free_vecs(cub, YES, NO);
	}
	if (*cub->line == NULL && malloc_flag == 0 && map == NA)
	{
		close(fd);
		free_vecs(cub, YES, YES);
	}
}

void	parse_file(t_cub *cub, char *map_path)
{
	char	*line;
	int	fd;

	line = NULL;
	cub->file = map_path;
	cub->line = &line;
	fd = open_validate_file(cub, map_path, ".cub", NA);
	parse_until_map(cub, fd);
	parse_map(cub, fd);
	cub->line = NULL;
	close(fd);
}
