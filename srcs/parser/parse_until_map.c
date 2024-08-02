/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_until_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:08:29 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:40:29 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		init_inds(t_indices *inds);
void		init_tex_count(t_count *count);
void		parse_push_textures(t_parser *parser, t_indices *inds);
void		parse_push_colors(t_parser *parser, char **type_id, t_indices *inds,
				t_count *count);

static int	not_yes(t_parser *parser, char c)
{
	if (c == '\0')
	{
		free(parser->line);
		parser->line = NULL;
		return (EMP_LINE);
	}
	return (NA);
}

static void	identifiers_type(t_parser *parser, char **type_id, int *type_info,
		t_count *count)
{
	if (!ft_strncmp(*type_id, "NO", 2))
	{
		count->no++;
		*type_info = NO;
	}
	if (!ft_strncmp(*type_id, "SO", 2))
	{
		count->so++;
		*type_info = SO;
	}
	if (!ft_strncmp(*type_id, "WE", 2))
	{
		count->we++;
		*type_info = WE;
	}
	if (!ft_strncmp(*type_id, "EA", 2))
	{
		count->ea++;
		*type_info = EA;
	}
	if (count->no > 1 || count->so > 1 || count->we > 1 || count->ea > 1)
		free_exit(parser, type_id, TEXREPEAT);
}

static int	type_identifier(t_parser *parser, t_indices *inds, t_count *count)
{
	char	*type_id;
	int		type_id_info;

	type_id_info = FT;
	type_id = NULL;
	type_id = ft_substr(parser->line, inds->st, inds->end - inds->st);
	if (type_id == NULL)
		free_vecs(parser, YES, NULL, NULL);
	identifiers_type(parser, &type_id, &type_id_info, count);
	if (type_id_info != FT)
	{
		free(type_id);
		if (vec_push(parser->textures_info, &type_id_info) == 0)
			free_exit(parser, &type_id, NULL);
		return (TEXTURE);
	}
	validate_type_identifier(parser, &type_id);
	parse_push_colors(parser, &type_id, inds, count);
	return (FT);
}

static int	parse_push_lineinfo(t_parser *parser, int fd, t_count *count)
{
	t_indices	inds;
	char		c;
	int			malloc_flag;

	init_inds(&inds);
	malloc_flag = 0;
	parser->line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(parser, malloc_flag, NA, fd);
	skip_spaces(parser->line, &inds.st);
	c = parser->line[inds.st];
	if (c == '1' || c == '\0')
		return (not_yes(parser, c));
	inds.end = inds.st;
	next_strings_end(parser->line, &inds.end, 0);
	if (type_identifier(parser, &inds, count) == TEXTURE)
		parse_push_textures(parser, &inds);
	free(parser->line);
	parser->line = NULL;
	return (YES);
}

void	parse_until_map(t_parser *parser, int fd)
{
	int		qontinue;
	t_count	count;
	int		tids;

	init_tex_count(&count);
	qontinue = FT;
	tids = 0;
	while (qontinue != NA)
	{
		qontinue = parse_push_lineinfo(parser, fd, &count);
		if (qontinue == YES)
			tids++;
	}
	if (tids < TOT_TIDS)
		free_vecs(parser, YES, TIDS, NULL);
}
