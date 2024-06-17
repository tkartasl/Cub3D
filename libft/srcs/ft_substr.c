/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 09:35:38 by tkartasl          #+#    #+#             */
/*   Updated: 2023/11/09 09:33:12 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*cptr;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	if (len < ft_strlen(s) - start)
		cptr = malloc((len + 1) * sizeof(char));
	else
		cptr = malloc((ft_strlen(s) - start + 1) * sizeof(char));
	if (cptr == NULL)
		return (NULL);
	while (i < len && s[start] != 0)
	{
		cptr[i] = s[start];
		i++;
		start++;
	}
	cptr[i] = 0;
	return (cptr);
}
