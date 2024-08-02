/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:00:41 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/22 13:32:55 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	game_usage(void);
void	create_threads(t_data *data);

void	game_play(t_data *data)
{
	raycaster(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_cursor_hook(data->mlx, &mouse_hook, data);
	mlx_loop_hook(data->mlx, &movement, data);
	mlx_loop(data->mlx);
}

int	main(int argc, char **argv)
{
	t_parser	parser;
	t_data		data;

	if (argc == 2)
	{
		init_parser(&parser);
		parse_file(&parser, argv[1]);
		init_data_mlx(&data, &parser);
		create_threads(&data);
		game_play(&data);
		freedata_exit(&data, EXIT_SUCCESS, YES, NA);
	}
	game_usage();
	return (SUCCESS);
}
