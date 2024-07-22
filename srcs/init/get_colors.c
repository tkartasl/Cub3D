/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:13:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/09 14:18:23 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	get_ceiling_color(t_parser *parser, t_data *data)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(parser->ceiling, R);
	green = *(int *)vec_get(parser->ceiling, G);
	blue = *(int *)vec_get(parser->ceiling, B);
	data->colors[0] = get_rgba(red, green, blue, A);
}

void	get_floor_color(t_parser *parser, t_data *data)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(parser->floor, R);
	green = *(int *)vec_get(parser->floor, G);
	blue = *(int *)vec_get(parser->floor, B);
	data->colors[1] = get_rgba(red, green, blue, A);
}

void	get_colors(t_parser *parser, t_data *data)
{
	get_ceiling_color(parser, data);
	get_floor_color(parser, data);
	data->colors[W] = get_rgba(0, 0, 0, A);
	data->colors[O] = get_rgba(255, 255, 255, A);
}
