/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/21 12:07:37 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_data *data, char direction)
{
	if (direction == 'R' )
	{
		data->player_angle += 0.1;
		if (data->player_angle > 2 * PI)
			data->player_angle -= 2 * PI;
		data->playerdir_x = cos(data->player_angle) * 10;
		data->playerdir_y = sin(data->player_angle) * 10;
	}
	if (direction == 'L')
	{
		data->player_angle -= 0.1;
		if (data->player_angle < 0)
			data->player_angle += 2 * PI;
		data->playerdir_x = cos(data->player_angle) * 10;
		data->playerdir_y = sin(data->player_angle) * 10;
	}
}

void	move_player(t_data *data, char direction)
{
	if (direction == 'W')
	{
		data->camera_x += (int)data->playerdir_x;
		data->camera_y += (int)data->playerdir_y;
	}
	if (direction == 'A')
	{
		data->camera_x += (int)data->playerdir_y;
		data->camera_y -= (int)data->playerdir_x;
	}
	if (direction == 'S')
	{
		data->camera_x -= (int)data->playerdir_x;
		data->camera_y -= (int)data->playerdir_y;
	}
	if (direction == 'D')
	{
		data->camera_x -= (int)data->playerdir_y;
		data->camera_y += (int)data->playerdir_x;
	}
}

void	movement(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player(data, 'W');
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player(data, 'A');
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player(data, 'S');
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player(data, 'D');
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, 'L');
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, 'R');
	cast_rays(data);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
