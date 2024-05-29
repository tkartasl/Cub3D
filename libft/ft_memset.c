/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:57:37 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/02 14:44:03 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	u;
	unsigned char	*p;

	p = b;
	u = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		(*(unsigned char *)b = u);
		i++;
		b++;
	}
	return (p);
}
