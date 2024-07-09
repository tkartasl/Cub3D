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

#include "../../includes/cub3D.h"

void	file_error(char *path, int use_errno)
{
	if (use_errno == YES)
	{
		ft_putstr_fd("cub3d: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(strerror(errno), 2);
		ft_putstr_fd("", 2);
	}
	ft_putstr_fd("cub3d: ", 2);
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": is not valid map file", 2);
	exit(EXIT_FAILURE);
}

void	game_usage(void)
{
	printf("%s\n", USAGE);
}
