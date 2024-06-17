/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:57:19 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/06 17:04:03 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_chckset(char const *s1, char const *set)
{
	while (*set != 0)
	{
		if (*set == *s1)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*s;
	int		i;
	int		n;

	if (!s1 || !set)
		return (0);
	i = 0;
	n = 0;
	while (s1[i] != 0 && ft_chckset(&s1[i], set) == 1)
	{
		i++;
		n++;
	}
	while (s1[i] != 0)
		i++;
	i = i - 1;
	while (i > 0 && ft_chckset(&s1[i], set) == 1)
	{
		i--;
	}
	i = i + 1;
	s = ft_substr(s1, n, i - n);
	return (s);
}
