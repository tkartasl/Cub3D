/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/18 13:03:44 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_data *data, char direction)
{
	if (direction == 'R' )
	{
		data->player_angle += 0.2;
		if (data->player_angle > 2 * PI)
			data->player_angle -= 2 * PI;
		data->playerdir_x = cos(data->player_angle) * 10;
		data->playerdir_y = sin(data->player_angle) * 10;
	}
	if (direction == 'L')
	{
		data->player_angle -= 0.2;
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
	}
	if (direction == 'S')
	{
		data->camera_x -= (int)data->playerdir_x;
		data->camera_y -= (int)data->playerdir_y;
	}
	if (direction == 'D')
	{
		data->camera_x -= (int)data->playerdir_y;
	}
}

void	key_hook_movement(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		rotate_player(data, 'R');
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		rotate_player(data, 'L');
	if (keydata.key == MLX_KEY_W && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'W');
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'A');
	if (keydata.key == MLX_KEY_S && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'S');
	if (keydata.key == MLX_KEY_D && (keydata.action == MLX_REPEAT
		|| keydata.action == MLX_PRESS))
		move_player(data, 'D');
	cast_rays(data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}
