/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:00:41 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/19 13:23:33 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	game_usage(void)
{
	printf("%s\n", USAGE);
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
		raycaster(&data);
		freedata_exit(&data, EXIT_SUCCESS, YES);
	}
	game_usage();
	return (SUCCESS);
}
