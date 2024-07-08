/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:16:12 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/08 13:19:38 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_player_dir(t_camera *cam)
{
	double	oct;

	oct = 0.78539816;
	if (cam->angle < NORTH + oct && cam->angle > NORTH - oct)
		return (SO);
	else if (cam->angle < SOUTH + oct
		&& cam->angle > SOUTH - oct)
		return (NO);
	else if (cam->angle < WEST + oct
		&& cam->angle > WEST - oct)
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
		if (mapx >= 0 && mapx < data->map_width && mapy >= 0
			&& mapy < data->map_height)
		{
			if (data->map[mapy][mapx] == '1')
				mlx_put_pixel(data->minimap, x, y, get_rgba(0, 0, 0, 255));
			else
				mlx_put_pixel(data->minimap, x, y, get_rgba(10, 200, 99, 200));
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
	int				x;
	int				cx;
	int				cy;
	static int		prev_dir;

	x = 0;
	cx = cam->cx;
	cx -= MUNITSIZE / MSCALE * UNITSIZE;
	if (prev_dir != get_player_dir(cam))
	{
		mlx_delete_image(data->mlx, data->player);
		mlx_delete_image(data->mlx, data->minimap);
		prev_dir = get_player_dir(cam);
		get_arrow_textures(data, prev_dir);
		if (mlx_image_to_window(data->mlx, data->minimap, 10, 10) < 0)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
		if (mlx_image_to_window(data->mlx, data->player, 165, 165) < 0)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
	}
	while (x < MINI_WIDTH)
	{
		drawstripe(data, x, cx, cam->cy);
		++x;
		cx += MSCALE;
	}
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
