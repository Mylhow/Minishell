
/*
**      -- TOKENIZER --
**      Includes tokenize(char *raw_command) to split an unparsed command into
**      a t_cmd_token list.
*/

#include "token.h"
#include "libft_mem.h"
#include <stdlib.h>

t_cmd_token         *tokenize(char *raw_cmd)
{
    char        quotes;
    int         parenthesis;
    int         i;
    char        *param;
    t_cmd_token *token_list;
    t_cmd_token *first;

    quotes = 0;
    i = 0;
    token_list = NULL;
    param = raw_cmd;
    parenthesis = 0;
    if (!*raw_cmd)
        return (NULL);
    while (*raw_cmd)
    {
        i++;
        if (*raw_cmd == '(')
            parenthesis ++;
        if (*raw_cmd == ')')
            parenthesis --;

        if (*raw_cmd == QUOTE_SINGLE || *raw_cmd == QUOTE_DOUBLE)
        {
            if (quotes == *raw_cmd)
                quotes = QUOTE_NONE;
            else
                quotes = *raw_cmd;
        }
 
        if (*raw_cmd == ' ' && quotes == QUOTE_NONE && !parenthesis)
        {
            if (i != 1)
            {
                if (!token_list)
                {
                    token_list = create_next_token(NULL, param, i);
                    first = token_list;
                }
                else
                    token_list = create_next_token(&token_list, param, i);
            }
            param = raw_cmd + 1;
            i = 0;
        }
        raw_cmd ++;
    }
    if (i != 0)
    {
        if (token_list)
            token_list = create_next_token(&token_list, param, i + 1);
        else
            first = create_next_token(NULL, param, i + 1);
    }
    //NOTE: IF (QUOTES != NONE) HERE THERE IS AN UNCLOSED QUOTE
    return (first ? first : 0);
}



void            destroy_token_list(t_cmd_token  **list)
{
    t_cmd_token *tmp;

    if (list)
    {
        while (*list)
        {
            tmp = (*list)->next;
            wrfree((*list)->value);
            wrfree(*list);
            *list = tmp;
        }
    }
}