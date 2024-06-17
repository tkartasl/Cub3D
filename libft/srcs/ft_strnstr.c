/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:44:36 by tkartasl          #+#    #+#             */
/*   Updated: 2024/03/01 14:12:46 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != 0 && *s2 != 0)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (haystack == 0 && len == 0)
		return (NULL);
	if (ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	if (*needle == 0 || needle == 0)
		return ((char *)haystack);
	while (haystack[i] != 0 && i < len)
	{
		if (ft_strcmp(&haystack[i], needle) && (i + ft_strlen(needle)) <= len)
			return (&((char *)haystack)[i]);
		i++;
	}
	return (NULL);
}
