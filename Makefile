# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 12:11:11 by tkartasl          #+#    #+#              #
#    Updated: 2024/06/17 10:08:56 by tkartasl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

NAME_BONUS = cub3D_bonus

SRCS = srcs/raycast.c \
		srcs/movement.c \
		srcs/drawing.c \
		srcs/dda.c \
		srcs/raycast_utils.c

#SRCS_BONUS =

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

LIBFT = libft/

MLXDIR = MLX42/build

MLX42_A = ${MLXDIR}/libmlx42.a

LIBFT_A = libft/libft.a

MAKE = make

FLAGS = -Wall -Wextra -Werror -Iincludes

MLX42_FLAGS = -Iinclude -ldl -lglfw -pthread -lm #-lglfw -L "/Users/$(USER)/.homebrew/opt/glfw/lib/"

CC = cc ${FLAGS}

CC_BONUS = cc -g -Wall -Wextra -Werror

all: ${NAME}

mlx42lib: ${MLX42_A} 

${MLX42_A}: ${MLXDIR}
	${MAKE} -C ${MLXDIR} -j4

${MLXDIR}:
	cmake MLX42 -B MLX42/build

%.o: %.c
	${CC} -o $@ -c $<

${NAME}: ${OBJS} ${LIBFT_A} ${MLX42_A}
	${CC} ${OBJS} ${LIBFT_A} ${MLX42_A} ${MLX42_FLAGS} -o ${NAME}

${LIBFT_A}:
	${MAKE} -C ${LIBFT}

bonus: ${NAME_BONUS}

${NAME_BONUS}: ${OBJS_BONUS} ${LIBFT_A} ${MLX42_A}
	${CC_BONUS} ${OBJS_BONUS} ${LIBFT_A} ${MLX42_A} ${MLX42_FLAGS} -o ${NAME_BONUS}

clean:
	${MAKE} clean -C ${LIBFT}
	rm -rf ${OBJS}
	rm -rf ${MLXDIR}
	rm -rf ${OBJS_BONUS}
	
fclean: clean
	rm -f ${NAME}
	rm -rf ${NAME_BONUS}
	${MAKE} fclean -C ${LIBFT}

re: fclean all

.PHONY: re, fclean, clean, all, mlx42lib bonus
