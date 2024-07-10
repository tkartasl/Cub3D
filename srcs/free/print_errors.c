/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:30:14 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/09 13:30:34 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

void	file_error(char *path, int use_errno, char *msg)
{
	if (use_errno == YES)
	{
		ft_putendl_fd(RED, 2);
		ft_putstr_fd("cub3d: ", 2);
		ft_putendl_fd(RESET, 2);
		ft_putendl_fd(YELLOW, 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(RESET, 2);
		ft_putendl_fd(CYAN, 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd("", 2);
		ft_putendl_fd(RESET, 2);
	}
	ft_putendl_fd(RED, 2);
	ft_putstr_fd("cub3d: ", 2);
	ft_putendl_fd(RESET, 2);
	ft_putendl_fd(MAGENTA, 2);
	ft_putendl_fd(msg, 2);
	ft_putendl_fd(RESET, 2);
	exit(EXIT_FAILURE);
}

void	game_usage(void)
{
	printf("%s\n", USAGE);
}
