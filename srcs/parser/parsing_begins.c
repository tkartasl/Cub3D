/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_begins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:20 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/26 13:19:17 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_until_map(t_parser *parser, int fd);
void	parse_map(t_parser *parser, int fd);

void	free_exit(t_parser *parser, char **type_id, char *msg)
{
	free(*type_id);
	free_vecs(parser, YES, msg, NULL);
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

void	eof_malloc_check(t_parser *parser, int malloc_flag, int map, int fd)
{
	if (parser->line == NULL && malloc_flag == 1)
	{
		close(fd);
		free_vecs(parser, YES, NULL, NULL);
	}
	if (parser->line == NULL && malloc_flag == 0 && map == NA)
	{
		close(fd);
		free_vecs(parser, YES, NOMAP, NULL);
	}
}

void	parse_file(t_parser *parser, char *map_path)
{
	int		fd;

	parser->line = NULL;
	parser->next_line = NULL;
	parser->file = map_path;
	fd = open_validate_file(parser, map_path, ".cub", NA);
	parse_until_map(parser, fd);
	parse_map(parser, fd);
	parser->line = NULL;
	close(fd);
}
