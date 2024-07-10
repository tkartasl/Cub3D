/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:11:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/10 20:58:53 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	fill_map_spaces(char **map, int maph);

static void	check_middle_lines(char **map, int x, int y, t_parser *parser)
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

void	check_first_last_line(char **map, int end, int y, t_parser *parser)
{
	int	x;
	int	index;

	x = 0;
	if (y == 0)
		index = y + 1;
	else
		index = y - 1;
	while (x < end)
	{
		if (map[y][x] == ' ' || map[y][x] == '\t')
			if (map[index][x] != '1')
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
		if (y == 0)
			check_first_last_line(map, x, y, parser);
		else if (y > 0 && y < (maph - 1))
			check_middle_lines(map, x, y, parser);
		else if (y == maph - 1)
			check_first_last_line(map, x, y, parser);
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
				else if (y > 0 && y < maph - 1 && (map[y + 1][x] == '0'
					|| map[y - 1][x] == '0'))
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
	fill_map_spaces(map, maph);
	check_holes_start(map, parser, maph);
	check_holes_end(map, parser, maph);
}
