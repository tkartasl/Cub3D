/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:11:50 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/07 17:11:51 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static	void	validate_push_horizontal(t_cub *cub, char **line)
{
	char	*dup_line;

	validate_horizontal(cub, *line);
	dup_line = ft_strdup(*line); // TODO: do something for whitespaces?
	free(*line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(cub, YES, NO);
	}
}

static	void	validate_push_middle(t_cub *cub)
{
	char	*dup_line;

	validate_middle(cub, *cub->line);
	dup_line = ft_strdup(*cub->line);
	free(*cub->line);
	if (vec_push(cub->map, &dup_line) == 0)
	{
		free(dup_line);
		free_vecs(cub, YES, NO);
	}
}

static	int	last_line(t_cub *cub, char *line)
{
	int	ind;
	int	len;
	int	count;

	ind = -1;
	count = 0;
	len = ft_strlen(line);
	while (++ind < len)
	{
		if (!ft_isspace(line[ind]))
			break ;
	}
	if (ind == len)
		free_vecs(cub, YES, YES);
	ind = -1;
	while (++ind < len)
	{
		count++;
		skip_spaces(line, &ind);
		if (count != 1 && line[ind] == '\0')
			break ;
		if (line[ind] != '1')
			return (NA);
	}
	return (YES);
}

static	void	something_follows_map(t_cub *cub, int fd)
{
	char	*line;
	int	malloc_flag;
	int	ind;

	malloc_flag = 0;
	ind = -1;
	line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(cub, malloc_flag, NA, fd);
	while (line)
	{
		ind = 0;
		while (line[ind])
		{
			if (!ft_isspace(line[ind]))
				free_exit(cub, &line, YES);
			ind++;
		}
		free(line);
		line = get_next_line(fd, &malloc_flag);
		eof_malloc_check(cub, malloc_flag, NA, fd);
	}
}

void	parse_map(t_cub *cub, int fd)
{
	int	malloc_flag;
	char	*line;

	malloc_flag = 0;
	validate_push_horizontal(cub, cub->line);
	*cub->line = get_next_line(fd, &malloc_flag);
	eof_malloc_check(cub, malloc_flag, YES, fd);
	while (*cub->line)
	{
		line = get_next_line(fd, &malloc_flag);
		if (last_line(cub, *cub->line) == YES && (!line || line[0] == '\0'))
			break ;
		if (*cub->line[0] == '\0' || *cub->line[0] == '0')
			free_vecs(cub, YES, YES);
		validate_push_middle(cub);
		*cub->line = line;
		eof_malloc_check(cub, malloc_flag, YES, fd);
	}
	if (*cub->line == NULL || cub->dir_info == 0)
		free_vecs(cub, YES, YES);
	validate_push_horizontal(cub, &(*cub->line));
	something_follows_map(cub, fd);
}
