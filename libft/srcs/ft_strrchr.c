/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 09:34:31 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/06 11:57:56 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	cc;

	i = 0;
	cc = (char)c;
	while (s[i] != 0)
		i++;
	while (i >= 0)
	{
		if (s[i] == cc)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
