/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:16:46 by uahmed            #+#    #+#             */
/*   Updated: 2024/07/23 10:47:49 by tkartasl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../libft/includes/libft.h"
# include <stdlib.h>
# include <unistd.h>

# ifndef FDS
#  define FDS 256
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

void	ft_freestr(char *s);
size_t	ft_strlen(const char *s);
char	*ft_writeline(char *lines, char *line, int *malloc_flag);
size_t	ft_newline(char *s);
char	*get_next_line(int fd, int *malloc_flag);

#endif
