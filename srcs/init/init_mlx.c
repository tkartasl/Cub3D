/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:46 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/08 12:51:19 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

static	void	init_player(t_data *data)
{
	if (data->player_angle == SOUTH - PI)
		get_arrow_textures(data, SO);
	else if (data->player_angle == NORTH + PI)
		get_arrow_textures(data, NO);
	else if (data->player_angle == WEST)
		get_arrow_textures(data, WE);
	else
	        get_arrow_textures(data, EA);
}

void	init_mlx(t_data *data)
{
	mlx_image_t	*screen;
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (mlx == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	data->mlx = mlx;
	screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	data->screen = screen;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	init_player(data);
}
