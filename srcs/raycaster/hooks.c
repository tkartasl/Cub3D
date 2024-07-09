/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:33:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/09 14:47:38 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	rotate_player(t_data *data, char direction, t_camera *cam);

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);//freedata_exit(data, EXIT_SUCCESS, YES, NA);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_data		*data;
	t_camera	cam;
	static int	old_xpos;

	data = param;
	get_camera(data, &cam);
	if (xpos <= old_xpos)
		rotate_player(data, 'L', &cam);
	else if (xpos > old_xpos)
		rotate_player(data, 'R', &cam);
	old_xpos = xpos;
	set_camera(data, &cam);
}
