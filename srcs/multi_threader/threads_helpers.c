/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:18:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/06 00:23:55 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_continues(t_data *data)
{
	unsigned int	status;

	pthread_mutex_lock(&data->layers_lock[STOP_FLG]);
	status = data->flag;
	pthread_mutex_unlock(&data->layers_lock[STOP_FLG]);
	return (status);
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
