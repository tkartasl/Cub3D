/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:18:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/06 00:23:55 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

int	game_continues(t_data *data)
{
	unsigned	int	status;

	pthread_mutex_lock(&data->layers_lock[STOP_FLG]);
	status = data->flag;
	pthread_mutex_unlock(&data->layers_lock[STOP_FLG]);
	return (status);
}
