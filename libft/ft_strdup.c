/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 08:52:52 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/01 09:49:34 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		n;
	size_t	i;
	char	*p;

	i = ft_strlen(s1);
	n = 0;
	p = malloc((i + 1) * sizeof(char));
	if (p == NULL)
		return (NULL);
	while (s1[n] != 0)
	{
		p[n] = s1[n];
		n++;
	}
	p[n] = 0;
	return (p);
}
