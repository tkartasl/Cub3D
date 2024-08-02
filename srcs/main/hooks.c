/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 09:33:51 by tkartasl          #+#    #+#             */
/*   Updated: 2024/07/26 13:23:41 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	rotate_player(t_data *data, char direction);

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(data->mlx);
}

void	mouse_hook(double xpos, double ypos, void *param)
{
	t_data		*data;
	static int	old_xpos;

	(void)ypos;
	data = param;
	if (xpos <= old_xpos)
		rotate_player(data, 'L');
	else if (xpos > old_xpos)
		rotate_player(data, 'R');
	old_xpos = xpos;
}
