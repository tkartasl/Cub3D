/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:46 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/22 13:35:20 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player(t_data *data)
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
	mlx_t		*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (mlx == NULL)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	data->mlx = mlx;
	screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		freedata_exit(data, EXIT_FAILURE, NA, YES);
	data->screen = screen;
	data->minimap = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	if (!data->minimap)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
	data->player = mlx_new_image(data->mlx, MINI_WIDTH, MINI_HEIGHT);
	if (!data->player)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	init_player(data);
	if (mlx_image_to_window(data->mlx, data->screen, 0, 0) < 0)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
	if (mlx_image_to_window(data->mlx, data->minimap, 10, 10) < 0)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
	if (mlx_image_to_window(data->mlx, data->player, 165, 165) < 0)
		freedata_exit(data, EXIT_FAILURE, YES, YES);
}
