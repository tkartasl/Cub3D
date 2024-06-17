/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_textures.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:07:35 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 17:07:36 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	parse_push_textures(t_cub *cub, t_indices *inds)
{
	char	*path;
	char	*line;
	int	end;

	line = *cub->line;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] == '\0')
		free_vecs(cub, YES, YES);
	inds->end = inds->st;
	next_strings_end(line, &inds->end, 0);
	// NOTE: the next 3 lines check if path is not followed by a spaces/+newline
	end = inds->end;
	skip_spaces(line, &end);
	if (end < (int)ft_strlen(line) && line[end] != '\0')
		free_vecs(cub, YES, YES);
	path = ft_substr(*cub->line, inds->st, inds->end - inds->st);
	if (path == NULL) // NOTE: malloc_fail
		free_vecs(cub, YES, NO);
	open_validate_file(cub, path, ".xpm", YES);
	if (vec_push(cub->textures_paths, &path) == 0)
	{
		free(path);
		free_vecs(cub, YES, NO);
	}
}
