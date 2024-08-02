/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:16:12 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/26 13:20:30 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_player_dir(t_camera *cam)
{
	double	oct;

	oct = 0.78539816;
	if (cam->angle < NORTH + oct && cam->angle > NORTH - oct)
		return (SO);
	else if (cam->angle < SOUTH + oct && cam->angle > SOUTH - oct)
		return (NO);
	else if (cam->angle < WEST + oct && cam->angle > WEST - oct)
		return (WE);
	else
		return (EA);
	return (4);
}

static void	drawstripe(t_data *data, int x, int cx, int cy)
{
	unsigned int	y;
	int				mapx;
	int				mapy;

	cy -= 10 / MSCALE * UNITSIZE;
	y = 0;
	mapx = cx / UNITSIZE;
	while (y < MINI_HEIGHT)
	{
		mapy = cy / UNITSIZE;
		if (mapy >= 0 && mapy < data->map_height && mapx >= 0
			&& mapx < *(int *)vec_get(data->map_width, mapy))
		{
			if (data->map[mapy][mapx] == '1')
				mlx_put_pixel(data->minimap, x, y, data->colors[W]);
			else
				mlx_put_pixel(data->minimap, x, y, data->colors[MF]);
		}
		else
			mlx_put_pixel(data->minimap, x, y, data->colors[O]);
		++y;
		cy += MSCALE;
	}
}

void	draw_minimap(t_data *data, t_camera *cam)
{
	int	x;
	int	cx;

	x = 0;
	cx = cam->cx;
	cx -= MUNITSIZE / MSCALE * UNITSIZE;
	while (x < MINI_WIDTH)
	{
		drawstripe(data, x, cx, cam->cy);
		++x;
		cx += MSCALE;
	}
}

void	*minimap(void *arg)
{
	t_data		*data;
	t_camera	cam;

	data = (void *)arg;
	while (game_continues(data))
	{
		get_camera(data, &cam);
		draw_minimap(data, &cam);
	}
	return (NULL);
}
