/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:57:57 by uahmed            #+#    #+#             */
/*   Updated: 2024/06/17 10:42:50 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

void	ft_freestr(char *s)
{
	if (s != NULL)
	{
		free(s);
		s = NULL;
	}
}

void	ft_copylines(char **new_line, char *line, char *lines)
{
	int	ind;
	int	i;

	ind = 0;
	if (line)
	{
		ind = -1;
		while (line[++ind])
			(*new_line)[ind] = line[ind];
	}
	i = 0;
	while (lines[i] && lines[i] != '\n')
	{
		(*new_line)[ind++] = lines[i];
		i++;
	}
	(*new_line)[ind] = '\0';
}

char	*ft_writeline(char *lines, char *line, int *malloc_flag)
{
	char	*new_line;
	size_t	lines_len;
	size_t	line_len;

	lines_len = ft_strlen(lines);
	line_len = 0;
	if (line != NULL)
		line_len = ft_strlen(line);
	if (ft_newline(lines))
	{
		lines_len = ft_newline(lines);
		lines_len--;
	}
	new_line = malloc(lines_len + line_len + 1);
	if (!new_line)
	{
		*malloc_flag = 1;
		ft_freestr(line);
		return (NULL);
	}
	ft_copylines(&new_line, line, lines);
	ft_freestr(line);
	return (new_line);
}

size_t	ft_newline(char *s)
{
	size_t	ind;

	if (!s)
		return (0);
	ind = -1;
	while (s[++ind])
	{
		if (s[ind] == '\n')
			return (++ind);
	}
	return (0);
}
