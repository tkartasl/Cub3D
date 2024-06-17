/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:01:33 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/30 14:01:35 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	char	check_wall_unit(t_cub *cub, int *ind, int first)
{
	char	c;

	if (first == YES)
		skip_spaces(*cub->line, ind);
	c = (*cub->line)[*ind];
	if (c != '1')
		free_vecs(cub, YES, YES);
	return (c);
}

static	void	check_update_direction_info(t_cub *cub, char c)
{
	if (cub->dir_info > 0)
		free_vecs(cub, YES, YES);
	cub->dir_info++;
}

static	char	ones_surround_spaces(t_cub *cub, char c, char prev_c, int *ind)
{
	if (ft_isspace(c) && prev_c != '1')
		free_vecs(cub, YES, YES);
	if (ft_isspace(c) && prev_c == '1')
	{
		skip_spaces(*cub->line, ind);
		c = (*cub->line)[*ind];
		if (c && c != '1')
			free_vecs(cub, YES, YES);
	}
	return (c);
}

void	validate_middle(t_cub *cub, char *line)
{
	int	ind;
	char	c;
	char	prev_c;
	int	len;

	ind = 0;
	len = ft_strlen(line);
	prev_c = check_wall_unit(cub, &ind, YES);
	c = line[++ind];
	while ((line)[ind+1])
	{
		c = ones_surround_spaces(cub, c, prev_c, &ind);
		if (c == '\0')
			return ;
		if (c == 'W' || c == 'N' || c == 'S' || c == 'E')
			check_update_direction_info(cub, c);
		else if (c != '1' && c != '0')
			free_vecs(cub, YES, YES);
		prev_c = c;
		c = (line)[++ind];
		if (c == '\0')
			return ;
	}
	check_wall_unit(cub, &ind, NA);
}

void	validate_horizontal(t_cub *cub, char *line)
{
	int	ind;
	int	len;
	int	count;

	ind = 0;
	count = 0;
	len = ft_strlen(line);
	skip_spaces(line, &ind);
	if (ind < len && line[ind] != '1')
		free_vecs(cub, YES, YES);
	while (++ind < (len - 1))
	{
		count++;
		skip_spaces(line, &ind);
		if (count != 1 && line[ind] == '\0')
			return ;
		if (line[ind] != '1' && !ft_isspace(line[ind]))
			free_vecs(cub, YES, YES);
	}
	if (ind < len && line[ind] != '1')
		free_vecs(cub, YES, YES);
}
