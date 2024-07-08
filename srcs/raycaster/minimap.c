/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 11:16:12 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/08 13:03:52 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static int	get_player_dir(t_data *data)
{
	double	oct;

	oct = 0.78539816;
	if (data->player_angle < NORTH + oct && data->player_angle > NORTH - oct)
		return (0);
	else if (data->player_angle < SOUTH + oct
		&& data->player_angle > SOUTH - oct)
		return (1);
	else if (data->player_angle < WEST + oct
		&& data->player_angle > WEST - oct)
		return (2);
	else
		return (3);
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

void	minimap(t_data *data)
{
	int				x;
	int				cx;
	int				cy;
	static int		prev_dir;

	x = 0;
	cx = data->camera_x;
	cx -= MUNITSIZE / MSCALE * UNITSIZE;
	if (prev_dir != get_player_dir(data))
	{
		mlx_delete_image(data->mlx, data->player);
		mlx_delete_image(data->mlx, data->minimap);
		prev_dir = get_player_dir(data);
		get_arrow_textures(data, prev_dir);
		if (mlx_image_to_window(data->mlx, data->minimap, 10, 10) < 0)
			freedata_exit(data, EXIT_FAILURE, YES);
		if (mlx_image_to_window(data->mlx, data->player, 165, 165) < 0)
			freedata_exit(data, EXIT_FAILURE, YES);
	}
	while (x < MINI_WIDTH)
	{
		drawstripe(data, x, cx, data->camera_y);
		++x;
		cx += MSCALE;
	}
}
