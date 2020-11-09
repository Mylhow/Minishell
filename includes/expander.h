
#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft.h"
# include <stdlib.h>

/*
**  QUOTE UTILS
*/

# define QUOTE_NONE     '\0'
# define QUOTE_SINGLE   '\''
# define QUOTE_DOUBLE   '\"'

char    get_quotes(char *current);

/*
**  STRING UTILS
*/
char	*replace_section
	(char *str, int index, const char *replace, size_t pattern_len);


/*
**  EXPANDERS
*/
int		expand_var(char **dst, const char *str);

int     expand_str(char **dst, char *simple_command);

#endif