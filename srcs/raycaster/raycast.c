/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/17 10:05:52 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
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
	while (x_pos < WIDTH)
	{
		data->rayinfo->dist_h = check_horizontal_hit(data);
		data->rayinfo->dist_v = check_vertical_hit(data);
		if (data->rayinfo->dist_v >= data->rayinfo->dist_h)
		{
			color = 150;
			data->rayinfo->raydist = data->rayinfo->dist_h;
		}
		if (data->rayinfo->dist_h >= data->rayinfo->dist_v)
		{
			color = 12;
			data->rayinfo->raydist = data->rayinfo->dist_v;
		}
		draw_walls(data, color, x_pos);
		x_pos++;
	}
}

void	assign_values(t_data *data, t_line *line, t_rayinfo *rayinfo)
{
	data->player_angle = 270 * PI / 180;
	rayinfo->ray_angle = data->player_angle;
	data->rayinfo = rayinfo;
	data->line = line;
	data->playerdir_x = cos(data->player_angle) * 10;
	data->playerdir_y = sin(data->player_angle) * 10;
	data->map_width = 5;
	data->map_height = 5;
	data->map_size = 25;
	data->camera_x = 96;
	data->camera_y = 224;		
}

int32_t	main(void)
{
	t_data		data;
	t_rayinfo	rayinfo;
	t_line		line;

	ft_memset(&rayinfo, 0, sizeof(t_rayinfo));
	ft_memset(&line, 0, sizeof(t_line));
	ft_memset(&data, 0, sizeof(t_data));
	assign_values(&data, &line, &rayinfo);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
        error();
	data.mlx = mlx;
	mlx_image_t* screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		error();
	data.screen = screen;
	memset(data.screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		error();
	cast_rays(&data);
	mlx_key_hook(mlx, &key_hook_movement, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
