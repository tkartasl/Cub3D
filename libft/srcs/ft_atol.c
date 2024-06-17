/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:26:47 by tkartasl          #+#    #+#             */
/*   Updated: 2024/01/19 14:30:54 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include "limits.h"

long	ft_atol(const char *str)
{
	int		neg;
	long	temp;

	temp = 0;
	neg = 1;
	while (*str != 0 && (*str == ' ' || *str == '\n' || *str == '\t'
			|| *str == '\v' || *str == '\f' || *str == '\r'))
		str++;
	if (*str == '-')
		neg = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != 0 && *str >= '0' && *str <= '9')
	{
		if (temp + (*str - 48) > (LONG_MAX / 10) && neg == -1)
			return (0);
		temp = temp * 10 + (*str - 48);
		str++;
	}
	if (temp == (LONG_MIN + 1))
		return (-1);
	return (temp * neg);
}
