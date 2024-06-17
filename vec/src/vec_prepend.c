/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_prepend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:54:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:54:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_prepend(t_vec *dst, t_vec *src)
{
	int	ind;

	ind = -1;
	if (!dst || !src)
		return (-1);
	while (++ind < (int)src->len)
		vec_insert(dst, &src->mem[ind * src->size], ind);
	return (1);
}
