/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 08:23:15 by tkartasl          #+#    #+#             */
/*   Updated: 2023/12/01 08:35:58 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putchar(int c)
{
	if (write(1, &c, 1) < 0)
		return (-1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	count;

	count = 0;
	if (!str)
	{
		if (write(1, "(null)", 6) < 0)
			return (-1);
		return (6);
	}
	while (*str != 0)
	{
		count = ft_write_fail_test(count, ft_putchar((int)*str));
		if (count < 0)
			return (-1);
		str++;
	}
	return (count);
}

int	ft_putnbr(long int n)
{
	int		i;
	char	arr[10];
	int		count;

	count = 0;
	i = 0;
	if (n == 0)
		return (write(1, "0", 1));
	if (n < 0)
	{
		count = ft_write_fail_test(count, write(1, "-", 1));
		if (count < 0)
			return (-1);
		n = n * (-1);
	}
	while (n > 0)
	{
		arr[i++] = n % 10 + '0';
		n /= 10;
	}
	while (i > 0 && count >= 0)
		count = ft_write_fail_test(count, ft_putchar(arr[--i]));
	return (count);
}

int	ft_write_fail_test(int count, int i)
{
	if (count < 0 || i < 0)
		return (-1);
	else
		return (count + i);
}
