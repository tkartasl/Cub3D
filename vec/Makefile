
NAME		:=	libvec.a
ERRTXT		:=	error.txt
OBJSDIR		:=	build
INCSDIR		:=	include
SRCSDIR		:=	src
DEPSDIR		:=	.deps
LIBFTDIR	:=	../libft
LIBFT		:=	$(LIBFTDIR)/libft.a

RM			:=	rm -rf
AR			:=	ar -rcs
CC			:=	cc
CFLAGS		:=	-Wall -Werror -Wextra
DEBUGFLAGS	=	-g -fsanitize=address
DEPFLAGS	=	-c -MT $$@ -MMD -MP -MF $(DEPSDIR)/$$*.d
SCREENCLR	:=	printf "\033c"
SLEEP		:=	sleep .1

SOURCES		:=	vec_append.c \
			vec_copy.c \
			vec_filter.c \
			vec_free.c \
			vec_from.c \
			vec_get.c \
			vec_insert.c \
			vec_iter.c \
			vec_map.c \
			vec_new.c \
			vec_pop.c \
			vec_prepend.c \
			vec_push.c \
			vec_reduce.c \
			vec_remove.c \
			vec_resize.c \
			vec_sort.c \
			
SOURCEDIR	:=	$(SRCSDIR)
BUILDDIR	:=	$(OBJSDIR)
DEPENDDIR	:=	$(DEPSDIR)
SRCS		:=	$(foreach file, $(SOURCES), $(shell find $(SOURCEDIR) -name $(file)))
OBJS		:=	$(patsubst $(SRCSDIR)/%.c, $(OBJSDIR)/%.o, $(SRCS))
DEPS		:=	$(patsubst $(SRCSDIR)/%.c, $(DEPSDIR)/%.d, $(SRCS))
INCS	 	:=	$(foreach header, $(INCSDIR), -I $(header))
INCS	 	+=	$(foreach header, $(LIBFTDIR)/$(INCSDIR), -I $(header))

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
	@printf "$(C)__      ________ _____ $(T)\n"
	@printf "$(C)\ \    / /  ____/ ____|$(T)\n"
	@printf "$(C) \ \  / /| |__ | |     $(T)\n"
	@printf "$(C)  \ \/ / |  __|| |     $(T)\n"
	@printf "$(C)   \  /  | |___| |____ $(T)\n"
	@printf "$(C)    \/   |______\_____|     by uahmed$(T)\n"
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
