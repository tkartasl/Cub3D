/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:54:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:54:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!dst || !src || index > dst->len)
		return (0);
	if (index == dst->len)
		return (vec_push(dst, src));
	if (dst->len * dst->size >= dst->mem_alloc)
	{
		if (vec_resize(dst, (dst->mem_alloc * 2) / dst->size) < 0)
			return (0);
	}
	ft_memmove(vec_get(dst, index + 1), vec_get(dst, index), (dst->len - index)
		* dst->size);
	ft_memcpy(vec_get(dst, index), src, dst->size);
	dst->len++;
	return (1);
}
