/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:42:46 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/18 15:45:11 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	init_mlx(t_data *data)
{
	mlx_image_t	*screen;
	mlx_image_t	*minimap;

	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (mlx == NULL)
		freedata_exit(data, EXIT_FAILURE);
	data->mlx = mlx;
	screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		freedata_exit(data, EXIT_FAILURE);
	data->screen = screen;
	minimap = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!minimap)
		freedata_exit(data, EXIT_FAILURE);
	data->minimap = minimap;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	ft_memset(data->screen->pixels, 255, MINI_WIDTH * MINI_HEIGHT * sizeof(int32_t));
}
