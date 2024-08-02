/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:44:48 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:41:07 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void		check_invalid_color(t_parser *parser, char *line, t_indices *inds,
				char **rgb);

static int	all_digits(char *rgb)
{
	int	ind;

	ind = -1;
	while (rgb[++ind])
	{
		if (!ft_isdigit(rgb[ind]))
			return (FT);
	}
	return (YES);
}

static char	*next_rgb(t_parser *parser, char *line, t_indices *inds)
{
	char	*rgb;

	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	inds->end = inds->st;
	if (line[inds->st] == '\0')
		free_vecs(parser, YES, INVALCOLOR, NULL);
	next_strings_end(line, &inds->end, 1);
	rgb = ft_substr(line, inds->st, inds->end - inds->st);
	if (rgb == NULL)
		free_vecs(parser, YES, NULL, NULL);
	if (all_digits(rgb) != YES)
	{
		free(rgb);
		free_vecs(parser, YES, INVALCOLOR, NULL);
	}
	--inds->counter;
	if (inds->counter == 0)
		check_invalid_color(parser, parser->line, inds, &rgb);
	return (rgb);
}

static void	skip_comma(t_parser *parser, char **rgb_s, t_indices *inds
	, int count)
{
	free(*rgb_s);
	if (count == 2)
		return ;
	inds->st = inds->end;
	skip_spaces(parser->line, &inds->st);
	if (parser->line[inds->st] != ',')
		free_vecs(parser, YES, INVALCOLOR, NULL);
	inds->st++;
	inds->end = inds->st;
}

static void	parse_color(t_parser *parser, t_indices *inds, int type)
{
	char	*rgb_s;
	int		rgb_n;
	int		count;

	count = -1;
	while (inds->counter && ++count < 3)
	{
		rgb_s = next_rgb(parser, parser->line, inds);
		rgb_n = ft_atoi(rgb_s);
		if (rgb_n > 255 || rgb_n < 0)
			free_exit(parser, &rgb_s, INVALCOLOR);
		if (type == FLOOR)
		{
			if (vec_push(parser->floor, &rgb_n) == 0)
				free_exit(parser, &rgb_s, INVALCOLOR);
		}
		else if (type == CEILING)
		{
			if (vec_push(parser->ceiling, &rgb_n) == 0)
				free_exit(parser, &rgb_s, INVALCOLOR);
		}
		skip_comma(parser, &rgb_s, inds, count);
	}
	if (inds->counter)
		free_vecs(parser, YES, INVALCOLOR, NULL);
}

void	parse_push_colors(t_parser *parser, char **type_id, t_indices *inds,
		t_count *count)
{
	if (!ft_strncmp(*type_id, "C", 1))
	{
		count->c++;
		if (count->c > 1)
			free_exit(parser, type_id, MOREFLOOR);
		free(*type_id);
		parse_color(parser, inds, CEILING);
		return ;
	}
	if (!ft_strncmp(*type_id, "F", 1))
	{
		count->f++;
		if (count->f > 1)
			free_exit(parser, type_id, MORECEILING);
		free(*type_id);
		parse_color(parser, inds, FLOOR);
		return ;
	}
	free_exit(parser, type_id, INVALCOLOR);
}
