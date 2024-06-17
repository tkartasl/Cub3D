/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_resize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:31 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 16:58:32 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

int	vec_resize(t_vec *src, size_t target_len)
{
	t_vec	new;

	if (!src)
		return (0);
	if (!src->mem)
		return (vec_new(src, target_len, src->size));
	if (!vec_new(&new, target_len, src->size))
		return (0);
	memcpy(new.mem, src->mem, src->len * src->size);
	new.len = src->len;
	vec_free(src);
	*src = new;
	return (1);
}
