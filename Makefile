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
SRCS_TERM	=	move.c handle_key.c utils.c init.c blocks.c escape.c ctrl.c insert_key.c backspace.c syntax_error.c syntax_error2.c syntax_tool.c commands.c historic.c
SRCS_EXEC	=	exec_str.c exec_utils.c exec_tree.c execbi.c
SRCS_EXPAND	=	expander.c expand_word.c expand_var.c expand_utils.c expand_quotes.c expand_bslash.c
SRCS_REDIR	=	redirect.c redirect_handler.c
SRCS_OTHER  =   ft_echo.c ft_env.c ft_export.c ft_unset.c ft_exit.c ft_cd.c ft_pwd.c
SRCS_PARS	=	creation_btree.c parsing_tools.c split_op_tok.c
SRCS_ENV	=	environement.c environement_utils.c
SRCS		=	$(addprefix $(PATH_SRC)/expand/, $(SRCS_EXPAND)) \
				$(addprefix $(PATH_SRC)/redirect/, $(SRCS_REDIR)) \
				$(addprefix $(PATH_SRC)/parsing/, $(SRCS_PARS)) \
				$(addprefix $(PATH_SRC)/exec/, $(SRCS_EXEC)) \
				$(addprefix $(PATH_SRC)/builtins/, $(SRCS_OTHER)) \
				$(addprefix $(PATH_SRC)/terminal/, $(SRCS_TERM)) \
				$(addprefix $(PATH_SRC)/env/, $(SRCS_ENV)) \
				$(addprefix $(PATH_SRC)/, main.c utilities.c)

OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	$(addprefix $(PATH_INC)/, terminal.h exec.h btree.h syntax_error.h exec.h expander.h sh_utils.h redirect.h environement.h)
LOG			=	$(PATH_LOG)/minishell.log
LIBFT		=	-L$(PATH_LIBFT) -lft -lcurses

# Commands of compilation
COMP		=	clang
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_DEB	=	-g3 -fsanitize=address
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

debug: init $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_DEB) $(COMP_ADD) -o minishell_debug $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

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
