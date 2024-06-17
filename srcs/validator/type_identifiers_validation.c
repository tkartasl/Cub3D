/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_identifiers_validation.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:28:26 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 17:28:27 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	check_invalid_color(t_cub *cub, char *line, t_indices *inds, char **rgb)
{
	skip_spaces(line, &inds->end);
	if (line[inds->end] != '\0' && !ft_isspace(line[inds->end]))
	{
		free(*rgb);
		free_vecs(cub, YES, YES);
	}
}

void	validate_type_identifier(t_cub *cub, char **type_id)
{
	if (ft_strlen(*type_id) > 1)
	{
		free(*type_id);
		free_vecs(cub, YES, YES);
	}
}
