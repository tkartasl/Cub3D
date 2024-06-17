/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:15:20 by tkartasl          #+#    #+#             */
/*   Updated: 2023/12/01 09:11:38 by tkartasl         ###   ########.fr       */
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
