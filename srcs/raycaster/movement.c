/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/06 00:27:34 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	rotate_player(t_data *data, t_camera *cam, char direction)
{
	if (direction == 'R')
	{
		cam->angle += 0.09;
		if (cam->angle >= 2 * PI)
			cam->angle -= 2 * PI;
		data->playerdir_x = cos(cam->angle) * 7.5;
		data->playerdir_y = sin(cam->angle) * 7.5;
	}
	if (direction == 'L')
	{
		cam->angle -= 0.09;
		if (cam->angle < 0)
			cam->angle += 2 * PI;
		data->playerdir_x = cos(cam->angle) * 7.5;
		data->playerdir_y = sin(cam->angle) * 7.5;
	}
}

static void	move_player_strafe(t_data *data, t_camera *cam, char key)
{
	int	offset[2];

	if (data->playerdir_x < 0)
		offset[X] = -20;
	else
		offset[X] = 20;
	if (data->playerdir_y < 0)
		offset[Y] = -20;
	else
		offset[Y] = 20;
	wall_collision_strafe(data, cam, key, offset);
}

static void	move_player_straight(t_data *data, t_camera *cam, char key)
{
	int	offset[2];

	if (data->playerdir_x < 0)
		offset[X] = -20;
	else
		offset[X] = 20;
	if (data->playerdir_y < 0)
		offset[Y] = -20;
	else
		offset[Y] = 20;
	wall_collision(data, cam, key, offset);
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
		move_player_straight(data, &cam, 'W');
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_strafe(data, &cam, 'A');
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_straight(data, &cam, 'S');
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_strafe(data, &cam, 'D');
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, &cam, 'L');
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, &cam, 'R');
	set_camera(data, &cam);
}
