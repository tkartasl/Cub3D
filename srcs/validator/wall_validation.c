/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:11:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/12 11:32:17 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

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

void	fill_map_spaces(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		while (map[y][x] != 0)
		{
			if (ft_strchr("01NESW", map[y][x]) == 0)
				map[y][x] = '.';
			x++;
		}
		x = 0;
		y++;
	}
}

int	check_surroundings(char **map, t_data *data, int x, int y)
{
	if (x + 1 < data->map_width)
	{
		if (map[y][x + 1] == '.')
			return (1);		
	}
	if (y + 1 < data->map_height)
	{
		if (map[y + 1][x] == '.')
			return (1);		
	}
	if (x - 1 >= 0)
	{
		if (map[y][x - 1] == '.')
			return (1);		
	}
	if (y - 1 >= 0)
	{
		if (map[y - 1][x] == '.')
			return (1);		
	}
	return (0);
}

void	check_holes(char **map, t_parser *parser, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		while (map[y][x] != 0)
		{
			if (map[y][x] == '0')
				if (check_surroundings(map, data, x, y) == 1)
					free_vecs(parser, YES, MAPHOLE, map);
			x++;
		}
		x = 0;
		y++;
	}	
}

void	find_mapholes(char **map, t_parser *parser, t_data *data)
{
	fill_map_spaces(map);
	check_holes(map, parser, data);
}
