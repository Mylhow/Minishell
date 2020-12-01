#ifndef SYNTAX_ERROR_H
# define SYNTAX_ERROR_H

# define TO_EXECUTE 0
# define MALLOC_ERROR 1
# define NEW_LINE 2
# define NEW_COMMAND 3
# define EXIT_SYNTAX_ERROR 4

# define MALLOC
# define WORD 0
# define OPERAT 1
# define PARENTH 2
# define REDIRECT 3

//SYNTAX_TOOLS_C
char	pass_quotes(char *str, int *index);
void	pass_blank(char *str, int *index);

//SYNTAX_ERROR_C
short	syntax_error(char *input);

#endif