/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:11:50 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/10 21:14:40 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate_horizontal(t_parser *parser, char *msg);
void	validate_middle(t_parser *parser);

static void	validate_push_horizontal(t_parser *parser, char *msg)
{
	char	*dup_line;

	validate_horizontal(parser, msg);
	dup_line = ft_strdup(parser->line);
	free(parser->line);
	if (vec_push(parser->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(parser, YES, NULL, NULL);
	}
}

static void	validate_push_middle(t_parser *parser)
{
	char	*dup_line;

	validate_middle(parser);
	dup_line = ft_strdup(parser->line);
	free(parser->line);
	parser->line = NULL;
	if (vec_push(parser->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(parser, YES, NULL, NULL);
	}
}

static int	last_line(t_parser *parser)
{
	int	ind;
	int	len;
	int	count;

	ind = -1;
	count = 0;
	len = ft_strlen(parser->line);
	while (++ind < len)
	{
		if (!ft_isspace(parser->line[ind]))
			break ;
	}
	if (ind == len)
		free_vecs(parser, YES, ALLSPACES, NULL);
	ind = -1;
	while (++ind < len)
	{
		count++;
		skip_spaces(parser->line, &ind);
		if (count != 1 && parser->line[ind] == '\0')
			break ;
		if (parser->line[ind] != '1')
			return (YES);
	}
	return (YES);
}

static void	something_follows_map(t_parser *parser, int fd)
{
	char	*line;
	int		malloc_flag;
	int		ind;

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
				free_exit(parser, &line, SOMETHING);
			ind++;
		}
		free(line);
		line = get_next_line(fd, &malloc_flag);
		eof_malloc_check(parser, malloc_flag, NA, fd);
	}
}

void	parse_map(t_parser *parser, int fd)
{
	int		malloc_flag;

	malloc_flag = 0;
	validate_push_horizontal(parser, FHWALL);
	parser->line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(parser, malloc_flag, YES, fd);
	while (parser->line)
	{
		parser->next_line = get_next_line(fd, &malloc_flag);
		if (last_line(parser) == YES && (!parser->next_line
				|| parser->next_line[0] == '\0'))
			break ;
		if (parser->line[0] == '\0' || parser->line[0] == '0')
			free_vecs(parser, YES, INVALMAP, NULL);
		validate_push_middle(parser);
		parser->line = ft_strdup(parser->next_line);
		free(parser->next_line);
		parser->next_line = NULL;
		eof_malloc_check(parser, malloc_flag, YES, fd);
	}
	if (parser->dir_info == 0)
		free_vecs(parser, YES, NOPLAYER, NULL);
	validate_push_horizontal(parser, LHWALL);
	something_follows_map(parser, fd);
}
