/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:11:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/10 17:01:03 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int			get_line_end(char *line);
void	fill_map_spaces(char **map);
void	check_first_line_end(char **map, int x, int y, t_parser *parser);

static void	check_mid_line_end(char **map, int x, int y, t_parser *parser)
{
	int	len_top;
	int	len_bot;

	len_top = get_line_end(map[y - 1]);
	len_bot = get_line_end(map[y + 1]);
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
	while (map[y][x] != 0)
	{
		if (map[y][x] == '0')
			free_vecs(parser, YES, MAPHOLE, map);
		x++;
	}
}

static void	check_last_line_end(char **map, int x, int y, t_parser *parser)
{
	int	len_top;

	len_top = get_line_end(map[y - 1]);
	if (x > len_top)
		x = len_top + 1;
	while (map[y][x] != 0)
	{
		if (map[y][x] == '0')
			free_vecs(parser, YES, MAPHOLE, map);
		x++;
	}
}

static	void	check_holes_end(char **map, t_parser *parser, int maph)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		x = get_line_end(map[y]);
		while (map[y][x] != 0)
		{
			if (y == 0 && x > get_line_end(map[y + 1]))
				check_first_line_end(map, x, y, parser);
			else if (y > 0 && y < (maph - 1))
				check_mid_line_end(map, x, y, parser);
			else if (y == (maph - 1))
				check_last_line_end(map, x, y, parser);
			++x;
		}
		x = 0;
		y++;
	}
}

static	void	check_holes_start(char **map, t_parser *parser, int maph)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		if (x == 0 && (map[y][x] == ' ' || map[y][x] == '\t'))
		{
			while (map[y][x] != '1')
			{
				if (y == 0 && map[y + 1][x] == '0')
					free_vecs(parser, YES, MAPHOLE, map);
				else if (y > 0 && y < maph - 1 && (map[y + 1][x] == '0' || map[y
						- 1][x] == '0'))
					free_vecs(parser, YES, MAPHOLE, map);
				else if (y == (maph - 1) && map[y - 1][x] == '0')
					free_vecs(parser, YES, MAPHOLE, map);
				++x;
			}
		}
		x = 0;
		y++;
	}
}

void	find_mapholes(char **map, t_parser *parser, int maph)
{
	fill_map_spaces(map);
	check_holes_start(map, parser, maph);
	check_holes_end(map, parser, maph);
}
