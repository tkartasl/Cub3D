/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:22:25 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/06 17:06:35 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		n;

	if (!s1 || !s2)
		return (0);
	n = 0;
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	while (s1[n] != 0)
	{
		s[n] = s1[n];
		n++;
	}
	while (*s2 != 0)
	{
		s[n] = *s2;
		n++;
		s2++;
	}
	s[n] = 0;
	return (s);
}
