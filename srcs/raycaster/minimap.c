/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:16:12 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/02 11:16:15 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	drawstripe(t_data *data, int x, int cx, int cy)
{
	unsigned	int	y;
	int			mapx;
	int			mapy;

	cy -= 10 / MSCALE * UNITSIZE;
	y = 0;
	mapx = cx / UNITSIZE;
	while (y < MINI_HEIGHT)
	{
		mapy = cy / UNITSIZE;
		if (mapx >= 0 && mapx < data->map_width && mapy >= 0 && mapy < data->map_height)
		{
			if (data->map[mapy][mapx] == '1')
				mlx_put_pixel(data->minimap, x, y, get_rgba(0, 0, 0, 255));
			else
				mlx_put_pixel(data->minimap, x, y, get_rgba(255, 255, 255, 255));
		}
		else
			mlx_put_pixel(data->minimap, x, y, get_rgba(255, 255, 255, 255));
		++y;
		cy += MSCALE;
	}
}

void	drawplayer(t_data *data)
{
	int	x;
	int	y;
	int	playerw;
	int	playerh;

	x = MINI_WIDTH / MSCALE - MUNITSIZE / MSCALE - 1;
	playerw = MINI_WIDTH / MSCALE + MUNITSIZE / MSCALE;
	while (++x < playerw)
	{
		y = MINI_HEIGHT / MSCALE - MUNITSIZE / MSCALE - 1;
		playerh = MINI_HEIGHT / MSCALE + MUNITSIZE / MSCALE;
		while (++y < playerh)
			mlx_put_pixel(data->minimap, x, y, get_rgba(0, 0, 0, 255));
	}
}

void	draw_minimap(t_data *data, t_camera *cam)
{
	int	x;
	int	cx;
	int	cy;

	x = 0;
	cx = cam->cx;
	cx -= MUNITSIZE / MSCALE * UNITSIZE;
	while (x < MINI_WIDTH)
	{
		drawstripe(data, x, cx, cam->cy);
		++x;
		cx += MSCALE;
	}
	drawplayer(data);
}

void	*minimap(void *arg)
{
	t_data	*data;
	t_camera	cam;

	data = (void *)arg;
	while (game_continues(data))
	{
		get_camera(data, &cam);
		draw_minimap(data, &cam);
	}
	return (NULL);
}
