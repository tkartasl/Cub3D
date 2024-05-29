/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:20:15 by tkartasl          #+#    #+#             */
/*   Updated: 2024/01/19 14:20:57 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*s;
	int		n;

	if (!s1 || !s2)
		return (0);
	n = 0;
	s = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == 0)
	{
		free (s1);
		return (0);
	}
	while (s1[n] != '\0')
	{
		s[n] = s1[n];
		n++;
	}
	while (*s2 != '\0')
	{
		s[n++] = *s2;
		s2++;
	}
	s[n] = 0;
	free (s1);
	return (s);
}
