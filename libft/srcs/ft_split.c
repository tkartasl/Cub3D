/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 12:41:48 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/09 11:05:22 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_strcount(const char *s, char c)
{
	int		t;
	int		n;
	int		i;
	size_t	count;

	count = 0;
	t = 0;
	n = 0;
	i = 0;
	while (s[t] != 0)
	{
		i = n;
		while (s[t] == c && s[t] != 0)
			t++;
		while (s[t] != c && s[t] != 0)
		{
			n++;
			t++;
		}
		if (n > i)
			count++;
	}
	return (count);
}

static void	ft_free(char **arr)
{
	int	n;

	n = 0;
	while (arr[n] != 0)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}

static char	**ft_putarr(char const *s, char **arr, char c, size_t n)
{
	unsigned int	k;
	size_t			t;

	t = 0;
	k = 0;
	while (s[k] != 0)
	{
		while (s[k] == c && s[k] != 0)
			k++;
		t = k;
		while (s[k] != c && s[k] != 0)
			k++;
		if (k > t)
		{
			arr[n] = ft_substr(s, t, k - t);
			if (arr[n] == 0)
			{
				ft_free(arr);
				return (0);
			}
			n++;
		}
	}
	arr[n] = 0;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char			**arr;
	size_t			n;
	size_t			i;

	if (!s)
		return (0);
	n = 0;
	i = ft_strcount(s, c);
	arr = malloc((i + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	arr = ft_putarr(s, arr, c, n);
	return (arr);
}
