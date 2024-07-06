/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 13:20:49 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/06 00:17:13 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/cub3D.h"

void	wall_collision(t_data *data, t_camera *cam, char key, int *offset)
{
	int	map[2];

	if (key == 'W')
	{
		map[X] = (cam->cx + offset[X]) / UNITSIZE;
		map[Y] = (cam->cy + offset[Y]) / UNITSIZE;
		if (data->map[cam->cy / UNITSIZE][map[X]] != '1')
			cam->cx += (int)data->playerdir_x;
		if (data->map[map[Y]][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_y;
	}
	if (key == 'S')
	{
		map[X] = (cam->cx - offset[X]) / UNITSIZE;
		map[Y] = (cam->cy - offset[Y]) / UNITSIZE;
		if (data->map[cam->cy / UNITSIZE][map[X]] != '1')
			cam->cx -= (int)data->playerdir_x;
		if (data->map[map[Y]][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_y;
	}

}

void	wall_collision_strafe(t_data *data, t_camera *cam, char key, int *offset)
{
	int	map[2];

	if (key == 'A')
	{
		map[X] = (cam->cx + offset[Y]) / UNITSIZE;
		map[Y] = (cam->cy - offset[X]) / UNITSIZE;
		if (data->map[cam->cy / UNITSIZE][map[X]] != '1')
			cam->cx += (int)data->playerdir_y;
		if (data->map[map[Y]][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_x;
	}
	if (key == 'D')
	{
		map[X] = (cam->cx - offset[Y]) / UNITSIZE;
		map[Y] = (cam->cy + offset[X]) / UNITSIZE;
		if (data->map[cam->cy / UNITSIZE][map[X]] != '1')
			cam->cx -= (int)data->playerdir_y;
		if (data->map[map[Y]][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_x;
	}
}
