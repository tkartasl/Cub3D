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

# include "../../includes/cub3D.h"

void	wall_collision(t_data *data, t_camera *cam, char key, int *offset)
{
	int	map[2];

	if (key == 'W')
	{
		map[0] = (cam->cx + offset[0]) / UNITSIZE;;
		map[1] = (cam->cy + offset[1]) / UNITSIZE;;
		if (data->map[cam->cy / UNITSIZE][map[0]] != '1')
			cam->cy += (int)data->playerdir_x;
		if (data->map[map[1]][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_y;
	}
	if (key == 'S')
	{
		map[0] = (cam->cx - offset[0]) / UNITSIZE;;
		map[1] = (cam->cy - offset[1]) / UNITSIZE;;
		if (data->map[cam->cy / UNITSIZE][map[0]] != '1')
			cam->cx -= (int)data->playerdir_x;
		if (data->map[map[1]][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_y;
	}

}

void	wall_collision_strafe(t_data *data, t_camera *cam, char key, int *offset)
{
	int	map[2];

	if (key == 'A')
	{
		map[0] = (cam->cx + offset[1]) / UNITSIZE;;
		map[1] = (cam->cy - offset[0]) / UNITSIZE;;
		if (data->map[cam->cy / UNITSIZE][map[0]] != '1')
			cam->cy += (int)data->playerdir_y;
		if (data->map[map[1]][cam->cx / UNITSIZE] != '1')
			cam->cy -= (int)data->playerdir_x;
	}
	if (key == 'D')
	{
		map[0] = (cam->cx - offset[1]) / UNITSIZE;;
		map[1] = (cam->cy + offset[0]) / UNITSIZE;;
		if (data->map[cam->cy / UNITSIZE][map[0]] != '1')
			cam->cx -= (int)data->playerdir_y;
		if (data->map[map[1]][cam->cx / UNITSIZE] != '1')
			cam->cy += (int)data->playerdir_x;
	}
}
