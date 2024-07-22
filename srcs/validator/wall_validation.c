/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:11:50 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/22 10:19:20 by tkartasl         ###   ########.fr       */
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


static void    check_middle_lines(char **map, int x, int y, t_parser *parser)
{
       int     len_top;
       int     len_bot;

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

int	check_surroundings(char **map, t_data *data, int x, int y)
{
	if (y + 1 < data->map_height)
	{
		if (ft_isspace(map[y + 1][x]) == 1)
			return (1);		
	}
	if (y - 1 >= 0)
	{
		if (ft_isspace(map[y - 1][x]) == 1)
			return (1);		
	}
	return (0);
}

void	check_mapholes(char **map, t_parser *parser, t_data *data)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y] != 0)
	{
		x = get_line_end(map[y]);
		if (y > 0 && y < data->map_height - 1)
			check_middle_lines(map, x, y, parser);
		x = 0;
		while (map[y][x] != 0)
		{
			if (ft_strchr("0NSWE", map[y][x]) != 0)
				if (check_surroundings(map, data, x, y) == 1)
					free_vecs(parser, YES, MAPHOLE, map);
			x++;
		}
		y++;
	}	
}

