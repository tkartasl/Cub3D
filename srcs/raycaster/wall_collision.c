/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:20:49 by tkartasl          #+#    #+#             */
/*   Updated: 2024/06/24 13:30:19 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	wall_collision(t_data *data, char key, int *new_x, int *new_y)
{
	int	offset_x;
	int	offset_y;

	if (data->playerdir_x < 0)
		offset_x = -20;
	else
		offset_x = 20;
	if (data->playerdir_y < 0)
		offset_y = -20;
	else
		offset_y = 20;
	if (key == 'W')
	{
		*new_x = (data->camera_x + offset_x) / 64;
		*new_y = (data->camera_y + offset_y) / 64;
	}
	else
	{
		*new_x = (data->camera_x - offset_x) / 64;
		*new_y = (data->camera_y - offset_y) / 64;
	}
}

void	wall_collision_strafe(t_data *data, char key, int *new_x, int *new_y)
{
	int	offset_x;
	int	offset_y;

	if (data->playerdir_x < 0)
		offset_x = -20;
	else
		offset_x = 20;
	if (data->playerdir_y < 0)
		offset_y = -20;
	else
		offset_y = 20;
	if (key == 'A')
	{
		*new_x = (data->camera_x + offset_y) / 64;
		*new_y = (data->camera_y - offset_x) / 64;
	}
	else
	{
		*new_x = (data->camera_x - offset_y) / 64;
		*new_y = (data->camera_y + offset_x) / 64;
	}
}
