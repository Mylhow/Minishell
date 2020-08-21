#ifndef TOKEN_H
# define TOKEN_H

#include "terminal.h"

# define QUOTE_NONE     0
# define QUOTE_SINGLE   '\''
# define QUOTE_DOUBLE   '"'

# define CMD_OP         0
# define CMD_EXEC       1
# define CMD_BUILTIN    2
# define CMD_ARG        3
# define CMD_PARENT     4

typedef int t_cmd_type;

typedef struct          s_cmd_token
{
    t_cmd_type          type;
    char                *value;

    struct s_cmd_token  *next;
    struct s_cmd_token  *back;
}                       t_cmd_token;


//  Utilities for get_token_type
int             is_token_builting(char *value);
int             is_token_operator(char * value);
//  Calculates the type of the token depending on it's value
t_cmd_type      get_token_type(t_cmd_token *last, char *value);

//  Creates a token that will be added to list
t_cmd_token     *create_next_token(t_cmd_token **list, char *value, int len);

//  Tokenize an unparsed command and destroys it.
#include "terminal.h"
int             main_token(t_term *term);
t_cmd_token     *tokenize(char *raw_cmd);
void            destroy_token_list(t_cmd_token  **list);

#endif