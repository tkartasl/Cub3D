/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:35 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 14:41:36 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	parse_push_textures(t_parser *parser, t_indices *inds)
{
	char	*path;
	char	*line;
	int	end;

	line = *parser->line;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] == '\0')
		free_vecs(parser, YES, YES);
	inds->end = inds->st;
	next_strings_end(line, &inds->end, 0);
	// NOTE: the next 3 lines check if path is not followed by a spaces/+newline
	end = inds->end;
	skip_spaces(line, &end);
	if (end < (int)ft_strlen(line) && line[end] != '\0')
		free_vecs(parser, YES, YES);
	path = ft_substr(*parser->line, inds->st, inds->end - inds->st);
	if (path == NULL) // NOTE: malloc_fail
		free_vecs(parser, YES, NO);
	open_validate_file(parser, path, ".xpm", YES);
	if (vec_push(parser->textures_paths, &path) == 0)
	{
		free(path);
		free_vecs(parser, YES, NO);
	}
}
