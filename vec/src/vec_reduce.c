/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_reduce.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:44:13 by uahmed            #+#    #+#             */
/*   Updated: 2024/05/22 15:44:15 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_reduce(void *acc, t_vec *src, void (*f)(void *, void *))
{
	int	ind;

	ind = -1;
	if (!acc || !src || !src->mem)
		return (-1);
	while (++ind < (int)src->len)
		(f)(acc, &src->mem[ind * src->size]);
	return (1);
}
