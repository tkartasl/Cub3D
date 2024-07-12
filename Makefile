# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkartasl <tkartasl@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/05 12:11:11 by tkartasl          #+#    #+#              #
#    Updated: 2024/07/12 11:32:57 by tkartasl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		:=	cub3D
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	includes
SRCSDIR		:=	srcs
DEPSDIR		:=	.deps
LIBFTDIR	:=	libft
LIBVECDIR 	:=	vec
LIBFT		:=	$(LIBFTDIR)/libft.a
LIBVEC		:=	$(LIBVECDIR)/libvec.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	:=	-g -fsanitize=address
DEPFLAGS	:=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

MLXDIR		:=	MLX42
MLXLIB		:=	$(MLXDIR)/$(OBJSDIR)/libmlx42.a
MLXBREW		:=	-L "/opt/homebrew/opt/glfw/lib/"
MLXFLAGS	:=	-ldl -lglfw -pthread -lm

ifeq ($(shell uname), Darwin)
	MLXFLAGS += $(MLXBREW)
endif

MODULES		:=	main \
				get_next_line \
				init \
				parser \
				validator \
				multi_threader \
				raycaster \
				minimap \
				free \

SOURCES 	:= 	main.c \
			init_parser.c \
			init_data.c \
			init_mlx.c \
			parsing_begins.c \
			parse_map.c \
			parse_validate_colors.c \
			parse_until_map.c \
			parse_validate_textures.c \
			type_identifiers_validation.c \
			map_validation.c \
			files_path_validation.c \
			get_next_line.c \
			get_next_line_utils.c \
			multi_threads.c \
			threads_helpers.c \
			raycast.c \
			minimap.c \
			errors.c \
			free_mem.c \
			print_errors.c \
			movement.c \
			drawing.c \
			get_colors.c \
			dda.c \
			raycast_utils.c \
			wall_collision.c \
			hooks.c \
			get_textures.c \
			wall_validation.c

SOURCEDIR	:=	$(addprefix $(SRCSDIR)/, $(MODULES))
BUILDDIR	:=	$(addprefix $(OBJSDIR)/, $(MODULES))
DEPENDDIR	:=	$(addprefix $(DEPSDIR)/, $(MODULES))
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBVECDIR)/$(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(MLXDIR)/include/MLX42, -I $(header))

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
	@if ! $(CC) -g $(INCS) $(DEPFLAGS) $$< -o $$@ 2> $(ERRTXT); then \
		printf "$(R)$(B)\nERROR!\n$(F)$(T)\n"; \
		printf "$(V)Unable to create object file:$(T)\n\n"; \
		printf "$(R)$(B)$$@$(T)\n"; \
		printf "$(Y)\n"; sed '$$d' $(ERRTXT); \
		printf "$(R)$(B)\n$(F)\nExiting...$(T)\n"; exit 1 ; \
	else \
		printf "$(C)$(B)☑$(T)$(V) $$<$ \n    $(C)⮑\t$(G)$(B)$$@$(T) \t\n"; \
	fi
endef

all: $(MLXLIB) $(LIBFT) $(LIBVEC) $(NAME)

$(MLXLIB):
	@$(SCREENCLR)
ifeq ("$(wildcard $(MLXDIR))", "")
	@echo "$(G)$(B)$(MLXDIR)$(T)$(V) not found, commencing download.$(T)\n"
	@git clone https://github.com/codam-coding-college/MLX42.git $(MLXDIR)
else
	@echo "\n$(V)Skipping download, $(G)$(B)$(MLXDIR)$(T)$(V) exists.$(T)"
endif
	@echo "\n$(V)Building $(G)$(B)MLX42$(T)$(V) binary...$(T)\n"
	@cmake $(MLXDIR) -B $(MLXDIR)/build && make -C $(MLXDIR)/build -j4

$(LIBFT):
	@make --quiet -C $(LIBFTDIR) all
	@make title

$(LIBVEC):
	@make --quiet -C $(LIBVECDIR) all
	@make title

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INCS) $^ $(LIBVEC) $(LIBFT) $(MLXLIB) $(MLXFLAGS) -o $@
	@make finish

debug: CFLAGS += $(DEBUGFLAGS)
debug: all

clean:
	@make --quiet -C $(LIBFTDIR) clean
	@make --quiet -C $(LIBVECDIR) clean
	@$(RM) $(OBJSDIR) $(DEPSDIR) $(ERRTXT)

fclean: clean
	@make --quiet -C $(LIBFTDIR) fclean
	@make --quiet -C $(LIBVECDIR) fclean
	@$(RM) $(MLXDIR)/$(OBJSDIR)
	@$(RM) $(NAME)

re: fclean all

nm:
	@$(foreach header, $(INCSDIR), norminette -R CheckDefine $(header))
	@$(foreach source, $(SRCSDIR), norminette -R CheckForbiddenSourceHeader $(source))

title:
	@$(SCREENCLR) && printf "\n"
	@printf "$(C)╔═╗╦ ╦╔╗ ╔═╗╔╦╗$(T)\n"
	@printf "$(C)║  ║ ║╠╩╗║╣  ║║  by tkartasl$(T)\n"
	@printf "$(C)╚═╝╚═╝╚═╝╚═╝═╩╝   & uahmed$(T)\n"
	@printf "$(G)$(B)$(F)\n$(T)\n"

finish:
	@printf "\n$(G)$(B)$(F)$(T)\n"
	@printf "$(C)╔═╗╦╔╗╔╦╔═╗╦ ╦╔═╗╔╦╗        $(V)$(B)$(NAME)$(T)\n"
	@printf "$(C)╠╣ ║║║║║╚═╗╠═╣║╣  ║║$(T)\n"
	@printf "$(C)╚  ╩╝╚╝╩╚═╝╩ ╩╚═╝═╩╝$(T)\n\n"

$(BUILDDIR) $(DEPENDDIR):
	@mkdir -p $@

$(DEPS):
	include $(wildcard $(DEPS))

$(foreach build, $(BUILDDIR), $(eval $(call cc_cmd, $(build))))

.PHONY: all debug clean fclean re title finish
