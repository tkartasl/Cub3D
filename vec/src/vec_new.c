/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:59:54 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 14:59:56 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_new(t_vec *dst, size_t len, size_t size)
{
	if (!size)
		return (0);
	if (len > 0)
	{
		dst->mem = (unsigned char *)malloc(len * size);
		if (!dst->mem)
			return (0);
	}
	else
		dst->mem = NULL;
	dst->size = size;
	dst->len = 0;
	dst->mem_alloc = size * len;
	return (1);
}
