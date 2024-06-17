/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validate_colors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:44:48 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 15:44:51 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void	check_invalid_color(t_cub *cub, char *line, t_indices *inds, char **rgb);

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

static	char	*next_rgb(t_cub *cub, char *line, t_indices *inds)
{
	char	*rgb;

	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	inds->end = inds->st;
	if (line[inds->st] == '\0')
		free_vecs(cub, YES, YES);
	next_strings_end(line, &inds->end, 1);
	rgb = ft_substr(line, inds->st, inds->end - inds->st);
	if (rgb == NULL)
		free_vecs(cub, YES, NO);
	if (all_digits(rgb) != YES)
	{
		// TODO: look for negative rgb values
		free(rgb);
		free_vecs(cub, YES, YES);
	}
	--inds->counter; // NOTE: might not need this counter
	if (inds->counter == 0) // NOTE: might not need this counter
		check_invalid_color(cub, *cub->line, inds, &rgb);
	return (rgb);
}

static	void	skip_comma(t_cub *cub, char *line, t_indices *inds, int count)
{
	if (count == 2)
		return ;
	inds->st = inds->end;
	skip_spaces(line, &inds->st);
	if (line[inds->st] != ',')
		free_vecs(cub, YES, YES);
	inds->st++;
	inds->end = inds->st;
}

static	void	parse_color(t_cub *cub, t_indices *inds, int type)
{
	char	*rgb_s;
	int	rgb_n;
	int	count;

	count = -1;
	while (inds->counter && ++count < 3) // NOTE: might not need this counter
	{
		rgb_s = next_rgb(cub, *cub->line, inds);
		rgb_n = ft_atoi(rgb_s);
		free(rgb_s);
		if (type == FLOOR)
		{
			if (vec_push(cub->floor, &rgb_n) == 0)
				free_exit(cub, &rgb_s, NO);
		}
		else if (type == CEILING)
		{
			if (vec_push(cub->ceiling, &rgb_n) == 0)
				free_exit(cub, &rgb_s, NO);
		}
		skip_comma(cub, *cub->line, inds, count);
	}
	if (inds->counter) // NOTE: might not need this counter
		free_vecs(cub, YES, YES);
}

void	parse_push_colors(t_cub *cub, char **type_id, t_indices *inds, t_count *count)
{
	if (!ft_strncmp(*type_id, "C", 1))
	{
		count->c++;
		if (count->c > 1)
			free_exit(cub, type_id, YES);
		free(*type_id);
		parse_color(cub, inds, CEILING);
		return ;
	}
	if (!ft_strncmp(*type_id, "F", 1))
	{
		count->f++;
		if (count->f > 1)
			free_exit(cub, type_id, YES);
		free(*type_id);
		parse_color(cub, inds, FLOOR);
		return;
	}
	free_exit(cub, type_id, YES); // TODO: print error
}
