/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:43:07 by tkartasl          #+#    #+#             */
/*   Updated: 2024/04/03 16:59:42 by vsavolai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_from_fd(int fd, char *remain)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	while (bytes_read && (ft_gnl_strchr(remain, '\n')) == '\0')
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(remain);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		remain = ft_gnl_strjoin(remain, buffer);
		if (remain == NULL)
			return (NULL);
	}
	free (buffer);
	return (remain);
}

char	*ft_extract_line(char *remain)
{
	int		i;
	char	*temp;

	i = 0;
	if (remain[i] == '\0')
		return (NULL);
	while (remain[i] != '\n' && remain[i])
		i++;
	temp = ft_gnl_substr(remain, 0, ++i);
	return (temp);
}

char	*ft_extract_remain(char *remain)
{
	int		i;
	char	*dup;

	i = 0;
	while (remain[i] != '\n' && remain[i])
		i++;
	if (remain[i] == '\0')
	{
		free(remain);
		return (NULL);
	}
	dup = ft_gnl_substr(remain, ++i, ft_gnl_strlen(remain));
	if (dup == NULL)
		return (NULL);
	free (remain);
	return (dup);
}

char	*get_next_line(int fd)
{
	static char	*remain;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	remain = ft_read_from_fd(fd, remain);
	if (remain == NULL)
		return (NULL);
	line = ft_extract_line(remain);
	remain = ft_extract_remain(remain);
	return (line);
}
