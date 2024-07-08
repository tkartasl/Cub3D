/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/08 13:04:16 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotate_player(t_data *data, char direction, t_camera *cam)
{
	if (direction == 'R')
	{
		cam->angle += 0.05;
		if (cam->angle >= 2 * PI)
			cam->angle -= 2 * PI;
		data->playerdir_x = cos(cam->angle) * 5.5;
		data->playerdir_y = sin(cam->angle) * 5.5;
	}
	if (direction == 'L')
	{
		cam->angle -= 0.05;
		if (cam->angle < 0)
			cam->angle += 2 * PI;
		data->playerdir_x = cos(cam->angle) * 5.5;
		data->playerdir_y = sin(cam->angle) * 5.5;
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

void	get_camera(t_data *data, t_camera *cam)
{
	pthread_mutex_lock(&data->layers_lock[CAMERA]);
	cam->cx = data->camera_x;
	cam->cy = data->camera_y;
	cam->angle = data->player_angle;
	pthread_mutex_unlock(&data->layers_lock[CAMERA]);
}

void	set_camera(t_data *data, t_camera *cam)
{
	pthread_mutex_lock(&data->layers_lock[CAMERA]);
	data->camera_x = cam->cx;
	data->camera_y = cam->cy;
	data->player_angle = cam->angle;
	pthread_mutex_unlock(&data->layers_lock[CAMERA]);
}

void	movement(void *param)
{
	t_data	*data;
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
}
