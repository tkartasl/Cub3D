/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:54:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:54:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_filter(t_vec *dst, t_vec *src, bool (*f)(void *))
{
	int	ind;

	ind = -1;
	if (!dst || !src)
		return (-1);
	if (!dst->mem)
	{
		if (vec_new(dst, dst->len, dst->size) < 0)
			return (-1);
	}
	while (++ind < (int)src->len)
	{
		if ((f)(&src->mem[ind * src->size]))
			if (vec_push(dst, &src->mem[ind * src->size]) < 0)
				return (-1);
	}
	return (1);
}
