/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:33 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/26 13:20:06 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	check_wall_unit(t_parser *parser, int *ind, int first, char *msg)
{
	char	c;

	if (first == YES)
		skip_spaces(parser->line, ind);
	else
		*ind = get_line_end(parser->line);
	c = (parser->line)[*ind];
	if (c != '1')
		free_vecs(parser, YES, msg, NULL);
	return (c);
}

static void	check_update_direction_info(t_parser *parser)
{
	if (parser->dir_info > 0)
		free_vecs(parser, YES, MOREPLAYER, NULL);
	parser->dir_info++;
}

static char	ones_surround_spaces(t_parser *parser, char c, char prev_c,
		int *ind)
{
	if (ft_isspace(c) && prev_c != '1')
		free_vecs(parser, YES, MAPHOLE, NULL);
	if (ft_isspace(c) && prev_c == '1')
	{
		skip_spaces(parser->line, ind);
		c = (parser->line)[*ind];
		if (c && c != '1')
			free_vecs(parser, YES, MAPHOLE, NULL);
	}
	return (c);
}

void	validate_middle(t_parser *parser)
{
	int		ind;
	char	c;
	char	prev_c;
	int		len;

	ind = 0;
	len = ft_strlen(parser->line);
	prev_c = check_wall_unit(parser, &ind, YES, FVWALL);
	c = parser->line[++ind];
	while ((parser->line)[ind + 1])
	{
		c = ones_surround_spaces(parser, c, prev_c, &ind);
		if (c == '\0')
			return ;
		if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
			check_update_direction_info(parser);
		else if (c != '1' && c != '0' && c != ' ' && c != '\t')
			free_vecs(parser, YES, INVALCHAR, NULL);
		prev_c = c;
		c = (parser->line)[++ind];
		if (c == '\0')
			return ;
	}
	check_wall_unit(parser, &ind, NA, LVWALL);
}

void	validate_horizontal(t_parser *parser, char *msg)
{
	int	ind;
	int	len;
	int	count;

	ind = 0;
	count = 0;
	len = ft_strlen(parser->line);
	skip_spaces(parser->line, &ind);
	if (ind < len && parser->line[ind] != '1')
		free_vecs(parser, YES, msg, NULL);
	while (++ind < (len - 1))
	{
		count++;
		skip_spaces(parser->line, &ind);
		if (count != 1 && parser->line[ind] == '\0')
			return ;
		if (parser->line[ind] != '1' && !ft_isspace(parser->line[ind]))
			free_vecs(parser, YES, msg, NULL);
	}
	ind = get_line_end(parser->line);
	if (parser->line[ind] != '1')
		free_vecs(parser, YES, msg, NULL);
}
