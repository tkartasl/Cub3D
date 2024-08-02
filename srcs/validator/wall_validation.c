/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:11:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/22 15:49:44 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_line_end(char *line)
{
	int	i;

	i = 0;
	while (line[i] != 0)
		i++;
	while (i >= 0 && line[i] != '1' && line[i] != '0')
		i--;
	return (i);
}

static void	check_middle_lines(t_data *data, int x, int y, t_parser *parser)
{
	int	len_top;
	int	len_bot;

	len_top = get_line_end(data->map[y - 1]);
	len_bot = get_line_end(data->map[y + 1]);
	if (len_bot <= len_top)
	{
		if (x > len_bot)
			x = len_bot + 1;
	}
	else
	{
		if (x > len_top)
			x = len_top + 1;
	}
	while (data->map[y][x] != 0)
	{
		if (data->map[y][x] == '0')
		{
			vec_free(data->map_width);
			free(data->map_width);
			free_vecs(parser, YES, MAPHOLE, data->map);
		}
		x++;
	}
}

static	void	check_surroundings(t_data *data, t_parser *parser, int x, int y)
{
	int	fail;

	fail = NA;
	if (y + 1 < data->map_height)
	{
		if (ft_isspace(data->map[y + 1][x]) == 1)
			fail = YES;
	}
	if (y - 1 >= 0)
	{
		if (ft_isspace(data->map[y - 1][x]) == 1)
			fail = YES;
	}
	if (fail == YES)
	{
		vec_free(data->map_width);
		free(data->map_width);
		free_vecs(parser, YES, MAPHOLE, data->map);
	}
}

void	check_mapholes(t_parser *parser, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (data->map[y] != 0)
	{
		x = get_line_end(data->map[y]);
		if (y > 0 && y < data->map_height - 1)
			check_middle_lines(data, x, y, parser);
		x = 0;
		while (data->map[y][x] != 0)
		{
			if (ft_strchr("0NSWE", data->map[y][x]) != 0)
				check_surroundings(data, parser, x, y);
			x++;
		}
		y++;
	}	
}
