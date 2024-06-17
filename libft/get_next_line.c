/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:43:07 by tkartasl          #+#    #+#             */
/*   Updated: 2023/12/01 09:08:07 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static void	ft_get_remain(char *buffer)
{
	int		i;
	int		j;
	char	temp[BUFFER_SIZE];

	j = 0;
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != 0)
		i++;
	if (buffer[i] == '\n')
	{
		i++;
		while (buffer[i] != 0)
			temp[j++] = buffer[i++];
		i = 0;
		while (i < j)
		{
			buffer[i] = temp[i];
			i++;
		}
		buffer[i] = 0;
	}
	else
		ft_bzero(buffer, BUFFER_SIZE + 1);
}

static char	*ft_trim_line(char *str)
{
	int		len;
	char	*temp;

	temp = 0;
	len = 0;
	while (str[len] != '\n' && str[len] != 0)
		len++;
	if (str[len] == '\n')
		len++;
	temp = ft_strndup(str, len);
	free (str);
	if (temp == 0)
		return (0);
	str = temp;
	return (str);
}

static char	*ft_cpy_line(int fd, char *buffer, char *str, size_t bcount)
{
	char	*line;

	line = 0;
	str = ft_strndup(buffer, ft_strlen(buffer));
	if (str == 0)
		return (0);
	while (ft_strchr(buffer, '\n') == 0 && bcount == BUFFER_SIZE)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		bcount = read(fd, buffer, BUFFER_SIZE);
		if (bcount < 0)
		{
			free (str);
			return (0);
		}
		if (bcount == 0)
			return (str);
		str = ft_strjoin_free(str, buffer);
		if (str == 0)
			return (0);
	}
	line = ft_trim_line(str);
	ft_get_remain(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	char			*str;
	static char		buffer[BUFFER_SIZE + 1];
	size_t			bcount;

	bcount = BUFFER_SIZE;
	str = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (read(fd, 0, 0) < 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		return (0);
	}
	str = ft_cpy_line(fd, buffer, str, bcount);
	if (str == 0)
		return (0);
	if (*str == 0)
	{
		free (str);
		return (0);
	}
	return (str);
}
