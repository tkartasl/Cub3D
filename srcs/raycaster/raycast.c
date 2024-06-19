/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/18 17:38:31 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void	cast_rays(t_data *data)
{
	int		x_pos;
	int		color;

	color = 0;
	x_pos = 0;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	data->rayinfo->ray_angle = data->player_angle - DEGREE * FOV / 2;
	reset_ray_angle(&data->rayinfo->ray_angle);
	draw_colors(data);
	while (x_pos < WIDTH)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data);
		data->rayinfo->dist_v = check_vertical_hit(data);
		if (data->rayinfo->dist_v >= data->rayinfo->dist_h)
		{
			color = 220;
			data->wall = 0;
			data->rayinfo->raydist = data->rayinfo->dist_h;
		}
		if (data->rayinfo->dist_h >= data->rayinfo->dist_v)
		{
			color = 100;
			data->wall = 1;
			data->rayinfo->raydist = data->rayinfo->dist_v;
		}
		draw_walls(data, color, x_pos);
		x_pos++;
	}
}

int32_t	raycaster(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		error();
	if (mlx_image_to_window(data->mlx, data->minimap, 0, 0) < 0)
		error();
	cast_rays(data);
	mlx_key_hook(data->mlx, &key_hook_movement, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
