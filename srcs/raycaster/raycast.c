/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:16:02 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/18 13:03:21 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

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
	int 	y;

	color = 0;
	x_pos = 0;
	y = 0;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	data->rayinfo->ray_angle = data->player_angle - DEGREE * FOV / 2;
	reset_ray_angle(&data->rayinfo->ray_angle);
	while (y < HEIGHT/2)
	{
		x_pos = 0;
		while (x_pos < WIDTH)
		{
			mlx_put_pixel(data->screen, x_pos, y, get_rgba(*(int *)vec_get(data->cub->ceiling, 0), *(int *)vec_get(data->cub->ceiling, 1), *(int *)vec_get(data->cub->ceiling, 2), 210));
			//mlx_put_pixel(data->screen, x_pos, y, get_rgba(0, 210, 0, 210));
			++x_pos;
		}
		++y;
	}
	while (y < HEIGHT)
	{
		x_pos = 0;
		while (x_pos < WIDTH)
		{
			mlx_put_pixel(data->screen, x_pos, y, get_rgba(*(int *)vec_get(data->cub->floor, 0), *(int *)vec_get(data->cub->floor, 1), *(int *)vec_get(data->cub->floor, 2), 210));
			//mlx_put_pixel(data->screen, x_pos, y, get_rgba(0, 0, 210, 210));
			++x_pos;
		}
		++y;
	}
	x_pos = 0;
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

void	extract_map_arr(t_cub *cub, t_data *data)
{
	int	x;
	int	y;
	char	**map;

	x = -1;
	y = -1;
	map = (char **)malloc(sizeof(char *) * (cub->map->len + 1));
	// TODO: malloc check
	while (++y < cub->map->len)
	{
		map[y] = *(char **)vec_get(cub->map, y);
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == 'S' || map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'E')
			{
				data->camera_y = (y * 64) + 32;
				data->camera_x = (x * 64) + 32;
				data->playerdir = map[y][x];
			}
		}
	}
	map[y] = NULL;
	data->map_height = y;
	data->map = map;
}

void	assign_values(t_data *data, t_line *line, t_rayinfo *rayinfo, t_cub *cub)
{
	extract_map_arr(cub, data);
	data->cub = cub;
	if (data->playerdir == 'N')
		data->player_angle = NORTH;
	else if (data->playerdir == 'W')
		data->player_angle = WEST;
	else if (data->playerdir == 'S')
		data->player_angle = SOUTH;
	else
		data->player_angle = EAST;
	rayinfo->ray_angle = data->player_angle;
	data->rayinfo = rayinfo;
	data->line = line;
	data->playerdir_x = cos(data->player_angle) * 10;
	data->playerdir_y = sin(data->player_angle) * 10;
	data->map_width = 25;
	data->map_size = 50;
}

int32_t	raycaster(t_cub *cub)
{
	t_data		data;
	t_rayinfo	rayinfo;
	t_line		line;

	ft_memset(&rayinfo, 0, sizeof(t_rayinfo));
	ft_memset(&line, 0, sizeof(t_line));
	ft_memset(&data, 0, sizeof(t_data));
	assign_values(&data, &line, &rayinfo, cub);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (!mlx)
		error();
	data.mlx = mlx;
	mlx_image_t* screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		error();
	data.screen = screen;
	ft_memset(data.screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	if (mlx_image_to_window(mlx, screen, 0, 0) < 0)
		error();
	cast_rays(&data);
	mlx_key_hook(mlx, &key_hook_movement, &data);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

