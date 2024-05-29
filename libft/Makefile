# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vsavolai <vsavolai@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/01 13:14:17 by tkartasl          #+#    #+#              #
#    Updated: 2024/04/03 13:59:17 by vsavolai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c\
	ft_memcmp.c \
	ft_strdup.c	\
	ft_strtrim.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_striteri.c \
	ft_substr.c \
	ft_calloc.c \
	ft_memmove.c \
	ft_strjoin.c \
	ft_tolower.c \
	ft_isalnum.c \
	ft_memset.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_isalpha.c \
	ft_putchar_fd.c \
	ft_strlcpy.c \
	ft_isascii.c \
	ft_putendl_fd.c \
	ft_strlen.c \
	ft_isdigit.c \
	ft_putnbr_fd.c \
	ft_strmapi.c \
	ft_isprint.c \
	ft_putstr_fd.c \
	ft_strncmp.c \
	ft_itoa.c \
	ft_split.c \
	ft_strnstr.c \
	ft_memchr.c \
	ft_strchr.c	\
	ft_strrchr.c \
	ft_lstnew_bonus.c\
	ft_lstsize_bonus.c \
	ft_lstlast_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstiter_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstmap_bonus.c \
	ft_printf.c \
	ft_printf_utils.c \
	get_next_line.c \
	get_next_line_utils.c \
	ft_recursive_power.c \
	ft_free_pointer_array.c \
	ft_strjoin_free.c \
	ft_strndup.c \
	ft_atol.c \
	ft_skip_whitespace.c

OBJS = ${SRCS:.c=.o}

FLAGS = -Wall -Wextra -Werror

CC = cc

all: ${NAME}

${NAME}: ${OBJS}
	ar -rcs ${NAME} ${OBJS}

${OBJS}: ${SRCS}
	${CC} ${FLAGS} -c ${SRCS}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all