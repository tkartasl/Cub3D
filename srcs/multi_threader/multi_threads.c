/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_threads.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 00:05:04 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/09 10:52:50 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3D.h"

void	create_threads(t_data *data)
{
	pthread_mutex_init(&data->layers_lock[CAMERA], NULL);
	pthread_mutex_init(&data->layers_lock[STOP_FLG], NULL);
	pthread_create(&data->layers[RAYCASTER], NULL, &raycaster, data);
	pthread_create(&data->layers[MINIMAP], NULL, &minimap, data);
}

void	join_threads(t_data *data)
{
	pthread_join(data->layers[RAYCASTER], NULL);
	pthread_join(data->layers[MINIMAP], NULL);
}

void	destroy_locks(t_data *data)
{
	pthread_mutex_destroy(&data->layers_lock[CAMERA]);
	pthread_mutex_destroy(&data->layers_lock[STOP_FLG]);
}
