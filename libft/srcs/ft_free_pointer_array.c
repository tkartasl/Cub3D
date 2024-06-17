/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pointer_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:13:34 by tkartasl          #+#    #+#             */
/*   Updated: 2024/01/19 14:17:37 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_free_pointer_array(char **arr)
{
	int	n;

	n = 0;
	while (arr[n] != 0)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
	arr = 0;
}
