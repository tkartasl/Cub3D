/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:54:47 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:54:49 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

void	*vec_get(t_vec *dst, size_t index)
{
	unsigned char	*new;

	if (index >= dst->len || !dst || !dst->mem)
		return (NULL);
	new = &dst->mem[index * dst->size];
	return (new);
}
