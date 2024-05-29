/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:22:24 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/01 14:16:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, int len)
{
	int		n;
	char	*p;

	n = 0;
	p = malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (0);
	while (n < len && s1[n] != 0)
	{
		p[n] = s1[n];
		n++;
	}
	p[n] = 0;
	return (p);
}
