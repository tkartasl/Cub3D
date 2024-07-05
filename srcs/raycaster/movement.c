/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:55:10 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/01 14:49:41 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	init_ray(t_vect *ray, t_camera *cam);

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
		offset[0] = -20;
	else
		offset[0] = 20;
	if (data->playerdir_y < 0)
		offset[1] = -20;
	else
		offset[1] = 20;
	wall_collision_strafe(data, cam, key, offset);
}

static void	move_player_straight(t_data *data, t_camera *cam, char key)
{
	int	offset[2];

	if (data->playerdir_x < 0)
		offset[0] = -20;
	else
		offset[0] = 20;
	if (data->playerdir_y < 0)
		offset[1] = -20;
	else
		offset[1] = 20;
	wall_collision(data, cam, key, offset);
}

void	set_camera(t_data *data, t_camera *cam)
{
	cam->cx = data->camera_x;
	cam->cy = data->camera_y;
	cam->angle = data->player_angle;
}

void	get_camera(t_data *data, t_camera *cam)
{
	data->camera_x = cam->cx;
	data->camera_y = cam->cy;
	data->player_angle = cam->angle;
}


void	movement(void *param)
{
	t_data	*data;
	t_camera	cam;
	t_vect		r;

	data = param;
	set_camera(data, &cam);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_player_straight(data, &cam, 'W');
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_player_strafe(data, &cam, 'A');
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_player_straight(data, &cam, 'S');
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_player_strafe(data, &cam, 'D');
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		rotate_player(data, &cam, 'L');
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		rotate_player(data, &cam, 'R');
	init_ray(&r, &cam);
	cast_rays(data, &cam, &r);
	minimap(data, &cam);
	get_camera(data, &cam);
}
