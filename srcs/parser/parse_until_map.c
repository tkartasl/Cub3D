/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_until_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:08:29 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 15:08:31 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3d.h"

void	init_inds(t_indices *inds);
void	init_tex_count(t_count *count);
void	parse_push_textures(t_cub *cub, t_indices *inds);
void	parse_push_colors(t_cub *cub, char **type_id, t_indices *inds, t_count *count);

static	int	not_yes(t_cub *cub, char c)
{
	if (c == '\0')
	{
		free(*cub->line);
		*cub->line = NULL;
		return (EMP_LINE);
	}
	return (NA);
}

static	void	identifiers_type(t_cub *cub, char **type_id, int *type_info, t_count *count)
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
	if (count->no > 1 || count->so > 1 || count->we > 1
			|| count->ea > 1)
			free_exit(cub, type_id, YES);
}

static	int	type_identifier(t_cub *cub, t_indices *inds, t_count *count)
{
	char	*type_id;
	int	type_id_info;

	type_id_info = 42;
	type_id = NULL;
	type_id = ft_substr(*cub->line, inds->st, inds->end - inds->st);
	if (type_id == NULL)
		free_vecs(cub, YES, NO);
	identifiers_type(cub, &type_id, &type_id_info, count);
	if (type_id_info != 42)
	{
		free(type_id);
		if (vec_push(cub->textures_info, &type_id_info) == 0)
			free_exit(cub, &type_id, NO);
		return (TEXTURE);
	}
	validate_type_identifier(cub, &type_id);
	parse_push_colors(cub, &type_id, inds, count);
	return (42);
}

static	int	parse_push_lineinfo(t_cub *cub, int fd, t_count *count)
{
	t_indices	inds;
	char		c;
	int		malloc_flag;
	char		*line;

	init_inds(&inds);
	malloc_flag = 0;
	*cub->line = get_next_line(fd, &malloc_flag);
	line = *cub->line;
	eof_malloc_check(cub, malloc_flag, NA, fd);
	skip_spaces(*cub->line, &inds.st);
	c = line[inds.st];
	if (c == '1' || c == '\0')
		return (not_yes(cub, c));
	inds.end = inds.st;
	next_strings_end(*cub->line, &inds.end, 0);
	if (type_identifier(cub, &inds, count) == TEXTURE)
		parse_push_textures(cub, &inds);
	free(*cub->line);
	*cub->line = NULL;
	return (YES);
}

void	parse_until_map(t_cub *cub, int fd)
{
	int	qontinue;
	t_count	count;
	int	tids;

	init_tex_count(&count);
	qontinue = 42;
	tids = 0;
	while (qontinue != NA)
	{
		qontinue = parse_push_lineinfo(cub, fd, &count);
		if (qontinue == YES)
			tids++;
	}
	if (tids < TOT_TIDS)
		free_vecs(cub, YES, YES);
}
