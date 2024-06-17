/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:58:28 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/06 11:57:23 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_getlen(long int n)
{
	size_t	t;

	t = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		t++;
		n = n * (-1);
	}
	while (n > 0)
	{
		n /= 10;
		t++;
	}
	return (t);
}

static char	*ft_putnbr_mod(char *str, long int l, size_t len)
{
	if (l == 0)
	{
		*str = '0';
		return (str);
	}
	if (l < 0)
	{
		l = l * (-1);
	}
	while (l > 0)
	{
		str[--len] = (l % 10) + '0';
		l /= 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char		*str;
	size_t		len;
	long int	l;

	l = n;
	len = ft_getlen(l);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	str = ft_putnbr_mod(str, l, len);
	str[len] = 0;
	if (n < 0)
		str[0] = '-';
	return (str);
}
