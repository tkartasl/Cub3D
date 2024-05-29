/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 14:15:20 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/03 13:36:37 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_gnl_strchr(char *s, int c)
{
	char	cc;

	if (!s)
		return (0);
	cc = c;
	while (*s)
	{
		if (*s == cc)
			return (s);
		s++;
	}
	if (cc == '\0')
		return (s);
	return (0);
}

char	*ft_gnl_strcpy(char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s2 == NULL)
		return (NULL);
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = (char *)malloc(1 * sizeof(char));
		if (!s1)
		{
			free (s2);
			return (NULL);
		}
		s1[0] = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
	{
		free (s1);
		free (s2);
		return (NULL);
	}
	ft_gnl_strcpy(str, s1);
	ft_gnl_strcpy(str + ft_strlen(s1), s2);
	free(s1);
	return (str);
}

char	*ft_gnl_substr(char *s, unsigned int start, size_t	len)
{
	size_t	i;
	char	*sub;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (len > ft_strlen(&s[start]))
		sub = (char *)malloc(sizeof(char) * (ft_strlen(&s[start]) + 1));
	else
		sub = (char *)malloc((len + 1) * sizeof(char));
	if (!sub)
	{
		free (s);
		return (NULL);
	}
	if (start >= ft_strlen(s))
		start = ft_strlen(s);
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
