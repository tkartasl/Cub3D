/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:54:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:54:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

void	vec_map(t_vec *dst, t_vec *src, void (*f)(void *))
{
	int	ind;

	ind = -1;
	if (!dst || !src)
		return ;
	if (!dst->mem)
		vec_new(dst, dst->len, dst->size);
	while (++ind < (int)src->len)
		(f)(&src->mem[ind * src->size]);
	memcpy(dst->mem, src->mem, src->len * src->size);
}
