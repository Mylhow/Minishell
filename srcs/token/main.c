#include "token.h"
#include "libft_gnl.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "terminal.h"

int main(void)
{
    char        *unparsed_cmd;
    t_cmd_token *token_list;
    t_cmd_token *tmp;
    int         notnull;


    init_term();
    printf ("$>");
    fflush(stdout);
    while (get_next_line(0, &unparsed_cmd))
    {
        token_list = tokenize(unparsed_cmd);
        notnull = 0;
        while (token_list)
        {
            if (token_list->type == CMD_ARG)
                printf ("[-- %s]", token_list->value);
            else if (token_list->type == CMD_EXEC)
                printf ("[<%s>]", token_list->value);
            else if (token_list->type == CMD_BUILTIN)
                printf ("[>%s<]", token_list->value);
            else if (token_list->type == CMD_PARENT)
                printf ("[prim exec : ( %s )]", token_list->value);
            else if (token_list->type == CMD_OP)
                printf ("{%s}", token_list->value);
            else
                printf ("[%s]", token_list->value);
            if (token_list->next)
                printf (" ; ");
            tmp = token_list->next;
            token_list = tmp;
            notnull = 1;
        }
        destroy_token_list(&token_list);

        if (notnull)
            printf ("\n");
        printf ("$>");
        fflush(stdout);
        wrfree(unparsed_cmd);
    }
    return (0);
}












/*
    EXAMPLE FORK PWD
*/
/*
void pwd()
{
    if (fork() == 0)
    {
        char *argv[] = {"/bin/pwd"};
        char *newargv[] = { *argv, NULL };
        char *newenviron[] = { NULL };

        execve(argv[0], newargv, newenviron);
        kill(0, 0);
    }
    else
        wait(NULL);
}*/
