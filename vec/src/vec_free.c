/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:00:14 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 15:00:15 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "vec.h"

void	vec_free(t_vec *vec)
{
	if (!vec || vec->mem_alloc == 0)
		return ;
	free(vec->mem);
	vec->mem = NULL;
	vec->len = 0;
	vec->size = 0;
	vec->mem_alloc = 0;
}
