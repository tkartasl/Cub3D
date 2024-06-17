/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:08:39 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 17:08:40 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (0);
	if (dst->mem == NULL)
	{
		if (!vec_new(dst, 1, dst->size))
			return (0);
	}
	if (dst->len * dst->size >= dst->mem_alloc)
	{
		if (!vec_resize(dst, dst->len * 2))
			return (0);
	}
	ft_memcpy(&dst->mem[dst->len * dst->size], src, dst->size);
	dst->len++;
	return (1);
}
