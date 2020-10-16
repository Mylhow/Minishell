.PHONY: all clean fclean re

# Name of file
NAME		=	minishell

# Name directory
PATH_INC	=	includes
PATH_SRC	=	srcs
PATH_OBJ	=	objs
PATH_LOG	=	logs
PATH_LIBFT	=	lib/libft

# List of sources
SRCS_TOKEN	=	token.c token_utils.c
SRCS_TERM	=	init_term.c utils.c handle_key.c
SRCS_EXEC	=	exec_str.c exec_utils.c redirect.c
SRCS_OTHER  =   ft_echo.c ft_env.c export.c env_utils.c
SRCS		=	$(addprefix $(PATH_SRC)/exec/, $(SRCS_EXEC)) $(addprefix $(PATH_SRC)/token/, $(SRCS_TOKEN)) $(addprefix $(PATH_SRC)/builtins/, $(SRCS_OTHER)) $(addprefix $(PATH_SRC)/terminal/, $(SRCS_TERM)) $(SRCS_ENV) $(addprefix $(PATH_SRC)/, main.c)
OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	$(addprefix $(PATH_INC)/, minishell.h terminal.h token.h env.h)
LOG			=	$(PATH_LOG)/minishell.log
LIBFT		=	-L$(PATH_LIBFT) -lft -lcurses

# Commands of compilation
COMP		=	clang
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_ADD	=	-I$(PATH_LIBFT)/$(PATH_INC) -I$(PATH_INC)

# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\033[38;5;184m
_GREEN		=	\033[38;5;46m
_RESET		=	\033[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME)
	@ echo "$(_SUCCESS) Compilation done"

init:
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_LOG))
	@ make -C $(PATH_LIBFT)

$(NAME): $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -o $(NAME) $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

$(PATH_OBJ)/%.o : $(PATH_SRC)/%.c  $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -c $< -o $@) >> $(LOG) 2>&1
	@ echo "$(_INFO) Compilation of $*"

clean:
	@ $(RM) -rf $(PATH_OBJ)
	@ echo "$(_INFO) Deleted files and directory"
	@ make -C $(PATH_LIBFT) clean

fclean: clean
	@ $(RM) -rf $(NAME)
	@ $(RM) -rf $(PATH_LOG)
	@ make -C $(PATH_LIBFT) fclean

re: fclean all
