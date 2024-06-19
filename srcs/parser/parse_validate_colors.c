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

# include "../../includes/cub3D.h"

void	check_invalid_color(t_parser *parser, char *line, t_indices *inds, char **rgb);

static	int	all_digits(char *rgb)
{
	int	ind;

	ind = -1;
	while (rgb[++ind])
	{
		if (!ft_isdigit(rgb[ind]))
			return (42);
	}
	return (YES);
}

static	char	*next_rgb(t_parser *parser, char *line, t_indices *inds)
{
	char	*rgb;

	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	inds->end = inds->st;
	if (line[inds->st] == '\0')
		free_vecs(parser, YES, YES);
	next_strings_end(line, &inds->end, 1);
	rgb = ft_substr(line, inds->st, inds->end - inds->st);
	if (rgb == NULL)
		free_vecs(parser, YES, NO);
	if (all_digits(rgb) != YES)
	{
		// TODO: look for negative rgb values
		free(rgb);
		free_vecs(parser, YES, YES);
	}
	--inds->counter; // NOTE: might not need this counter
	if (inds->counter == 0) // NOTE: might not need this counter
		check_invalid_color(parser, *parser->line, inds, &rgb);
	return (rgb);
}

static	void	skip_comma(t_parser *parser, char *line, t_indices *inds, int count)
{
	if (count == 2)
		return ;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] != ',')
		free_vecs(parser, YES, YES);
	inds->st++;
	inds->end = inds->st;
}

static	void	parse_color(t_parser *parser, t_indices *inds, int type)
{
	char	*rgb_s;
	int	rgb_n;
	int	count;

	count = -1;
	while (inds->counter && ++count < 3) // NOTE: might not need this counter
	{
		rgb_s = next_rgb(parser, *parser->line, inds);
		rgb_n = ft_atoi(rgb_s);
		free(rgb_s);
		if (type == FLOOR)
		{
			if (vec_push(parser->floor, &rgb_n) == 0)
				free_exit(parser, &rgb_s, NO);
		}
		else if (type == CEILING)
		{
			if (vec_push(parser->ceiling, &rgb_n) == 0)
				free_exit(parser, &rgb_s, NO);
		}
		skip_comma(parser, *parser->line, inds, count);
	}
	if (inds->counter) // NOTE: might not need this counter
		free_vecs(parser, YES, YES);
}

void	parse_push_colors(t_parser *parser, char **type_id, t_indices *inds, t_count *count)
{
	if (!ft_strncmp(*type_id, "C", 1))
	{
		count->c++;
		if (count->c > 1)
			free_exit(parser, type_id, YES);
		free(*type_id);
		parse_color(parser, inds, CEILING);
		return ;
	}
	if (!ft_strncmp(*type_id, "F", 1))
	{
		count->f++;
		if (count->f > 1)
			free_exit(parser, type_id, YES);
		free(*type_id);
		parse_color(parser, inds, FLOOR);
		return;
	}
	free_exit(parser, type_id, YES); // TODO: print error
}
