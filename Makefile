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
SRCS_TOKEN	=	$(addprefix $(PATH_SRC)/token/, token.c token_utils.c main.c)
SRCS_TERM	=	$(addprefix $(PATH_SRC)/terminal/, init_term.c utils.c)
SRCS_OTHER  =   $(addprefix $(PATH_SRC)/function/, ft_echo.c)
SRCS		=	$(SRCS_TOKEN) $(SRCS_OTHER) $(SRCS_TERM)
OBJS		=	$(addprefix $(PATH_OBJ)/, $(notdir $(SRCS:.c=.o)))
INCS		=	$(wildcard $(PATH_INC)/*.h)
LOG			=	$(addprefix $(PATH_LOG)/, $(patsubst %.a.log,%.log,$(NAME).log))
LIBFT		=	-L$(PATH_LIBFT) -lft -lcurses

# Commands of compilation
COMP		=	clang
COMP_FLAG	=	-Wall -Werror -Wextra
COMP_ADD	=	-I$(PATH_LIBFT)/$(PATH_INC) -I$(PATH_INC)

# Others Command
RM			=	/bin/rm

# Color Code and template code
_YELLOW		=	\e[38;5;184m
_GREEN		=	\e[38;5;46m
_RESET		=	\e[0m
_INFO		=	[$(_YELLOW)INFO$(_RESET)]
_SUCCESS	=	[$(_GREEN)SUCCESS$(_RESET)]

# Functions
all:	init $(NAME)
	@ echo "$(_SUCCESS) Compilation done in $$(($$(date +%S)-$$(cat  logs/time.log)))s"
	@ $(RM) -rf $(PATH_LOG)/time.log

init:
	@ date +%S > $(addprefix $(PATH_LOG)/, time.log)
	@ $(shell mkdir -p $(PATH_OBJ) $(PATH_LOG))
	@ make -C $(PATH_LIBFT)

$(NAME): $(OBJS) $(INCS)
	@ (set -x; $(COMP) $(COMP_FLAG) $(COMP_ADD) -o $(NAME) $(OBJS) $(LIBFT)) >> $(LOG) 2>&1

$(PATH_OBJ)/%.o : $(PATH_SRC)/*/%.c $(INCS)
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
