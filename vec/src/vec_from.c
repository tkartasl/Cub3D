/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:26 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 15:00:28 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_from(t_vec *dst, void *src, size_t len, size_t size)
{
	if (!dst || !src || !size)
		return (-1);
	if (vec_new(dst, len, size) < 0)
		return (-1);
	memcpy(dst->mem, src, dst->mem_alloc);
	dst->len = len;
	return (1);
}
