/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/12 11:42:20 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_player_dir(t_camera *cam);

void	rotate_player(t_data *data, char direction, t_camera *cam)
{
	static int		prev_dir;

	if (direction == 'R')
	{
		cam->angle += ROTATE_SPEED;
		if (cam->angle >= 2 * PI)
			cam->angle -= 2 * PI;
		data->playerdir_x = cos(cam->angle) * MOVE_SPEED;
		data->playerdir_y = sin(cam->angle) * MOVE_SPEED;
	}
	if (direction == 'L')
	{
		cam->angle -= ROTATE_SPEED;
		if (cam->angle < 0)
			cam->angle += 2 * PI;
		data->playerdir_x = cos(cam->angle) * MOVE_SPEED;
		data->playerdir_y = sin(cam->angle) * MOVE_SPEED;
	}
	if (prev_dir != get_player_dir(cam))
	{
		prev_dir = get_player_dir(cam);
		get_arrow_textures(data, prev_dir);
		if (mlx_image_to_window(data->mlx, data->player, 165, 165) < 0)
			freedata_exit(data, EXIT_FAILURE, YES, NA);
	}
}

static void	move_player_strafe(t_data *data, char key, t_camera *cam)
{
	int	new_x;
	int	new_y;

	new_x = 0;
	new_y = 0;
	if (key == 'A')
	{
		wall_collision_strafe(data, 'A', &new_x, &new_y);
		if (data->map[cam->cy / UNITSIZE][new_x] != '1')
			cam->cx += (int)data->playerdir_y;
		if (data->map[new_y][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_x;
	}
	if (key == 'D')
	{
		wall_collision_strafe(data, 'D', &new_x, &new_y);
		if (data->map[cam->cy / UNITSIZE][new_x] != '1')
			cam->cx -= (int)data->playerdir_y;
		if (data->map[new_y][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_x;
	}
}

static void	move_player_straight(t_data *data, char key, t_camera *cam)
{
	int	new_x;
	int	new_y;

	new_x = 0;
	new_y = 0;
	if (key == 'W')
	{
		wall_collision(data, 'W', &new_x, &new_y);
		if (data->map[cam->cy / UNITSIZE][new_x] != '1')
			cam->cx += (int)data->playerdir_x;
		if (data->map[new_y][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_y;
	}
	if (key == 'S')
	{
		wall_collision(data, 'S', &new_x, &new_y);
		if (data->map[cam->cy / UNITSIZE][new_x] != '1')
			cam->cx -= (int)data->playerdir_x;
		if (data->map[new_y][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_y;
	}
}

void	movement(void *param)
{
	t_data		*data;
	t_camera	cam;

	data = param;
	get_camera(data, &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_straight(data, 'W', &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_strafe(data, 'A', &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_straight(data, 'S', &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_strafe(data, 'D', &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, 'L', &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, 'R', &cam);
	set_camera(data, &cam);
	raycaster(data);
}
