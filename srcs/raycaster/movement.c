/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/24 13:21:55 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

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

void	move_player_strafe(t_data *data, char key)
{
	int	new_x;
	int	new_y;

	new_x = 0;
	new_y = 0;
	if (key == 'A')
	{
		wall_collision_strafe(data, 'A', &new_x, &new_y);
		if (data->map[data->camera_y][new_x] != '1')
			data->camera_x += (int)data->playerdir_y;
		if (data->map[new_y][data->camera_x] != '1')
			data->camera_y -= (int)data->playerdir_x;
	}
	if (key == 'D')
	{
		wall_collision_strafe(data, 'D', &new_x, &new_y);
		if (data->map[data->camera_y][new_x] != '1')
			data->camera_x -= (int)data->playerdir_y;
		if (data->map[new_y][data->camera_x] != '1')
			data->camera_y += (int)data->playerdir_x;
	}
}

void	move_player_straight(t_data *data, char key)
{
	int	new_x;
	int	new_y;

	new_x = 0;
	new_y = 0;
	if (key == 'W')
	{
		wall_collision(data, 'W', &new_x, &new_y);
		if (data->map[data->camera_y][new_x] != '1')
			data->camera_x += (int)data->playerdir_x;
		if (data->map[new_y][data->camera_x] != '1')
			data->camera_y += (int)data->playerdir_y;
	}
	if (key == 'S')
	{
		wall_collision(data, 'S', &new_x, &new_y);
		if (data->map[data->camera_y][new_x] != '1')
			data->camera_x -= (int)data->playerdir_x;
		if (data->map[new_y][data->camera_x] != '1')
			data->camera_y -= (int)data->playerdir_y;
	}
}

void	movement(void *param)
{
	t_data	*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_straight(data, 'W');
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_strafe(data, 'A');
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_straight(data, 'S');
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_strafe(data, 'D');
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
