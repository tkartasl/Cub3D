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

void	init_mlx(t_data *data)
{
	mlx_image_t	*screen;
	mlx_image_t	*minimap;
	
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true);
	if (mlx == NULL)
		freedata_exit(data, EXIT_FAILURE, NA);
	data->mlx = mlx;
	screen = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!screen)
		freedata_exit(data, EXIT_FAILURE, YES);
	data->screen = screen;
	minimap = mlx_new_image(mlx, 320, 320);
	if (!minimap)
		freedata_exit(data, EXIT_FAILURE, YES);
	data->minimap = minimap;
	ft_memset(data->screen->pixels, 255, WIDTH * HEIGHT * sizeof(int32_t));
	ft_memset(data->minimap->pixels, 255, 320 * 320 * sizeof(int32_t));
}
