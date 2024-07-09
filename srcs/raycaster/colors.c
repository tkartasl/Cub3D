/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 16:13:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/09 13:57:02 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void	get_ceiling_color(t_data *data)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(data->parser->ceiling, R);
	green = *(int *)vec_get(data->parser->ceiling, G);
	blue = *(int *)vec_get(data->parser->ceiling, B);
	data->ceiling_color = get_rgba(red, green, blue, A);
}

void	get_floor_color(t_data *data)
{
	int	red;
	int	green;
	int	blue;

	red = *(int *)vec_get(data->parser->floor, R);
	green = *(int *)vec_get(data->parser->floor, G);
	blue = *(int *)vec_get(data->parser->floor, B);
	data->floor_color = get_rgba(red, green, blue, A);
}
