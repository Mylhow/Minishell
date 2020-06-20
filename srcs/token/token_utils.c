
#include "token.h"

int          is_token_operator(char *value)
{
    if (!ft_strncmp(value, "|", 1))
        return (1);
    if (!ft_strncmp(value, "&&", 2))
        return (2);
    if (!ft_strncmp(value, "&", 1))
        return (3);
    if (!ft_strncmp(value, ";", 1))
        return (4);
    if (!ft_strncmp(value, ">", 1))
        return (5);
    if (!ft_strncmp(value, "<<", 2))
        return (6);
    if (!ft_strncmp(value, "<", 1))
        return (7);
    return (0);
}



int          is_token_builtin(char *value)
{
    if (!ft_strncmp(value, "echo", 4))
        return (1);
    if (!ft_strncmp(value, "cd", 2))
        return (2);
    if (!ft_strncmp(value, "pwd", 3))
        return (3);
    if (!ft_strncmp(value, "export", 6))
        return (4);
    if (!ft_strncmp(value, "unset", 5))
        return (5);
    if (!ft_strncmp(value, "env", 3))
        return (6);
    if (!ft_strncmp(value, "exit", 4))
        return (7);
    return (0);
}



t_cmd_type   get_token_type(t_cmd_token *last, char *value)
{
    if (is_token_operator(value))
        return (CMD_OP);

    if (!ft_strncmp(value, "(", 1) && !ft_strncmp(value + ft_strlen(value) - 1, ")", 1))
        return (CMD_PARENT);

    if (is_token_builtin(value))
        return (CMD_BUILTIN);
    else if (last)
    {
        if (last->type && (last->type == CMD_EXEC || last->type == CMD_BUILTIN || last->type == CMD_ARG))
            return (CMD_ARG);
    }
    return (CMD_EXEC);
}



t_cmd_token  *create_next_token(t_cmd_token **list, char *value, int len)
{
    t_cmd_token *token;
    
     if (!(token = (t_cmd_token *)malloc(sizeof(t_cmd_token))))
        return (NULL);
    if (!(token->value = (char *)ft_calloc(sizeof(char), len + 1)))
        return (NULL);
    ft_strlcpy(token->value, value, len);
    token->type = get_token_type((list) ? *list : 0, value);
    token->next = 0;
    token->back = 0;
    if (!list)
        return (token);
    
    while ((*list)->next)
        *list = (*list)->next;
    (*list)->next = token;
    token->back = *list;
    return (token);
}