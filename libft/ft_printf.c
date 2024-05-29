/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:19:38 by tkartasl          #+#    #+#             */
/*   Updated: 2023/12/01 09:12:27 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_puthex(char *format, unsigned int hex)
{
	char	str[16];
	int		count;
	int		i;

	i = 0;
	count = 0;
	if (hex == 0)
		return (write(1, "0", 1));
	while (hex != 0)
	{
		if (hex % 16 < 10)
			str[i] = hex % 16 + '0';
		else
		{
			if (*format == 'x')
				str[i] = hex % 16 + 'a' - 10;
			if (*format == 'X')
				str[i] = hex % 16 + 'A' - 10;
		}
		hex = hex / 16;
		i++;
	}
	while (i > 0 && count >= 0)
		count = ft_write_fail_test(count, ft_putchar(str[--i]));
	return (count);
}

static int	ft_putptr(unsigned long hex)
{
	char	str[16];
	int		count;
	int		i;

	count = 0;
	i = 0;
	if (hex == 0)
		return (write(1, "0x0", 3));
	count = ft_write_fail_test(count, write(1, "0x", 2));
	if (count < 0)
		return (-1);
	while (hex != 0)
	{
		if (hex % 16 < 10)
			str[i] = hex % 16 + '0';
		else
			str[i] = hex % 16 + 'a' - 10;
		hex = hex / 16;
		i++;
	}
	while (i > 0 && count >= 0)
		count = ft_write_fail_test(count, ft_putchar(str[--i]));
	return (count);
}

static int	ft_print_format(char format, va_list args)
{
	int	count;

	count = 0;
	if (format == '%')
		count = ft_write_fail_test(count, write(1, "%", 1));
	if (format == 'd' || format == 'i')
		count = ft_putnbr((long int)va_arg(args, int));
	if (format == 'u')
		count = ft_putnbr(va_arg(args, unsigned int));
	if (format == 's')
		count = ft_putstr(va_arg(args, char *));
	if (format == 'c')
		count = ft_putchar(va_arg(args, int));
	if (format == 'p')
		count = ft_putptr(va_arg(args, unsigned long long));
	if (format == 'x' || format == 'X')
		count = ft_puthex(&format, va_arg(args, unsigned int));
	return (count);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		count;

	count = 0;
	va_start(args, s);
	while (*s != 0)
	{
		if (*s == '%')
		{
			s++;
			if (*s != 0)
				count = ft_write_fail_test(count, ft_print_format(*s, args));
		}
		else
			count = ft_write_fail_test(count, write(1, s, 1));
		if (count < 0)
		{
			va_end(args);
			return (count);
		}
		if (*s != 0)
			s++;
	}
	va_end(args);
	return (count);
}
