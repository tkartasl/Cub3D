/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:13:31 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/10 20:36:20 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	check_holes_start(char **map, t_parser *parser, int maph);
void	check_holes_end(char **map, t_parser *parser, int maph);

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

static int	ft_skip_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

void	fill_map_spaces(char **map, int maph)
{
	int	x;
	int	y;
	int	line_end;

	line_end = 0;
	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		line_end = get_line_end(map[y]);
		x = ft_skip_space(map[y]);
		x++;
		if (y != 0 && y != maph - 1)
		{
			while (x < line_end)
			{
				if (map[y][x] == ' ' || map[y][x] == '\t')
					map[y][x] = '0';
				x++;
			}
		}
		x = 0;
		y++;
	}
}
