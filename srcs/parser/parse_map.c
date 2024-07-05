/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:11:50 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:39:18 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	validate_push_horizontal(t_parser *parser, char **line)
{
	char	*dup_line;

	validate_horizontal(parser, *line);
	dup_line = ft_strdup(*line);
	free(*line);
	if (vec_push(parser->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(parser, YES, NO);
	}
}

static	void	validate_push_middle(t_parser *parser)
{
	char	*dup_line;

	validate_middle(parser, *parser->line);
	dup_line = ft_strdup(*parser->line);
	free(*parser->line);
	if (vec_push(parser->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(parser, YES, NO);
	}
}

static	int	last_line(t_parser *parser, char *line)
{
	int	ind;
	int	len;
	int	count;

	ind = -1;
	count = 0;
	len = ft_strlen(line);
	while (++ind < len)
	{
		if (!ft_isspace(line[ind]))
			break ;
	}
	if (ind == len)
		free_vecs(parser, YES, YES);
	ind = -1;
	while (++ind < len)
	{
		count++;
		skip_spaces(line, &ind);
		if (count != 1 && line[ind] == '\0')
			break ;
		if (line[ind] != '1')
			return (NA);
	}
	return (YES);
}

static	void	something_follows_map(t_parser *parser, int fd)
{
	char	*line;
	int	malloc_flag;
	int	ind;

	malloc_flag = 0;
	ind = -1;
	line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(parser, malloc_flag, NA, fd);
	while (line)
	{
		ind = 0;
		while (line[ind])
		{
			if (!ft_isspace(line[ind]))
				free_exit(parser, &line, YES);
			ind++;
		}
		free(line);
		line = get_next_line(fd, &malloc_flag);
		eof_malloc_check(parser, malloc_flag, NA, fd);
	}
}

void	parse_map(t_parser *parser, int fd)
{
	int	malloc_flag;
	char	*line;

	malloc_flag = 0;
	validate_push_horizontal(parser, parser->line);
	*parser->line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(parser, malloc_flag, YES, fd);
	while (*parser->line)
	{
		line = get_next_line(fd, &malloc_flag);
		if (last_line(parser, *parser->line) == YES && (!line || line[0] == '\0'))
			break ;
		if (*parser->line[0] == '\0' || *parser->line[0] == '0')
			free_vecs(parser, YES, YES);
		validate_push_middle(parser);
		*parser->line = line;
		eof_malloc_check(parser, malloc_flag, YES, fd);
	}
	if (*parser->line == NULL || parser->dir_info == 0)
		free_vecs(parser, YES, YES);
	validate_push_horizontal(parser, &(*parser->line));
	something_follows_map(parser, fd);
}
