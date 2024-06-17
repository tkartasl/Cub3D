/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uahmed <uahmed@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 14:13:16 by uahmed            #+#    #+#             */
/*   Updated: 2024/04/12 14:13:19 by uahmed           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "../../libft/includes/libft.h"
# include "stdbool.h"
# include "stdlib.h"
# include "string.h"
# include "unistd.h"

typedef struct s_vec
{
	unsigned char	*mem;
	size_t			size;
	size_t			mem_alloc;
	size_t			len;
}					t_vec;

int					vec_copy(t_vec *dst, t_vec *src);
void				vec_free(t_vec *vec);
int					vec_new(t_vec *dst, size_t len, size_t size);
int					vec_from(t_vec *dst, void *src, size_t len, size_t size);
int					vec_resize(t_vec *src, size_t target_len);
int					vec_push(t_vec *dst, void *src);
int					vec_pop(void *dst, t_vec *src);
void				*vec_get(t_vec *dst, size_t index);
int					vec_insert(t_vec *dst, void *src, size_t index);
int					vec_remove(t_vec *src, size_t index);
int					vec_append(t_vec *dst, t_vec *src);
int					vec_prepend(t_vec *dst, t_vec *src);
void				vec_iter(t_vec *src, void (*f)(void *));
void				vec_map(t_vec *dst, t_vec *src, void (*f)(void *));
int					vec_filter(t_vec *dst, t_vec *src, bool (*f)(void *));
int					vec_reduce(void *acc, t_vec *src, void (*f)(void *,
							void *));
void				vec_sort(t_vec *src, int (*f)(void *, void *));

#endif
