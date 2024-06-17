/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 10:58:14 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/06 09:50:37 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t	n)
{
	unsigned char	*cp;
	size_t			i;
	unsigned char	uc;

	uc = (unsigned char)c;
	cp = (unsigned char *)s;
	i = 0;
	while (n > 0 && i < n - 1)
	{
		if (cp[i] == uc)
			return (&cp[i]);
		i++;
	}
	if (cp[i] == uc && i > 0)
		return (&cp[i]);
	if (cp[i] == uc && n == 1)
		return (&cp[i]);
	return (NULL);
}
