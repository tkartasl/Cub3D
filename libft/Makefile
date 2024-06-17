# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkorpela <mkorpela@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/08 14:29:18 by mkorpela          #+#    #+#              #
#    Updated: 2024/05/22 10:03:03 by mkorpela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	libft.a
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	includes
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

SOURCES		:=	ft_atoi.c\
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
			ft_isspace.c \
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
			ft_recursive_power.c \
			ft_free_pointer_array.c \
			ft_strjoin_free.c \
			ft_strndup.c \
			ft_atol.c \
			ft_skip_whitespace.c
			


SOURCEDIR	:=	$(SRCSDIR)
BUILDDIR	:=	$(OBJSDIR)
DEPENDDIR	:=	$(DEPSDIR)
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))

F			=	=====================================
B			=	\033[1m
T			=	\033[0m
G			=	\033[32m
V			=	\033[35m
C			=	\033[36m
R			=	\033[31m
Y			=	\033[33m

vpath %.c $(SOURCEDIR)

define cc_cmd
$1/%.o: %.c | $(BUILDDIR) $(DEPENDDIR)
	@if ! $(CC) $(CFLAGS) $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRTXT); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $$<$ \n    $(C)⮑\t$(G)$(B)$$@$(T) \t\n"; \
	fi
endef

all: title $(NAME) finish

$(NAME): $(OBJS)
	@$(AR) $@ $^

debug: CFLAGS += $(DEBUGFLAGS)
debug: all

clean:
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRTXT)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

title:
	@$(SCREENCLR) && printf "\n"
	@printf "$(C)╦  ╦╔╗ ╔═╗╔╦╗$(T)\n"
	@printf "$(C)║  ║╠╩╗╠╣  ║ $(T)\n"
	@printf "$(C)╩═╝╩╚═╝╚   ╩             by tkartasl$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"

finish:
	@printf "\n$(G)$(B)$(F)$(T)\n"
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗          $(V)$(B)$(NAME)$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call cc_cmd, $(build))))

.PHONY: all debug clean fclean re title finish
