/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 09:05:47 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/13 12:46:16 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char	*dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	t;
	size_t	j;

	if (dstsize == 0 && dst == 0)
		return (ft_strlen(src));
	j = ft_strlen(dst);
	i = 0;
	t = 0;
	while (dst[i] != 0)
		i++;
	while (i < dstsize - 1 && src[t] != 0 && dstsize != 0)
	{
		dst[i] = src[t];
		i++;
		t++;
	}
	dst[i] = 0;
	if (dstsize < j)
		return (ft_strlen(src) + dstsize);
	else
		return (j + ft_strlen(src));
}
