#include "token.h"
#include "libft_gnl.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include "terminal.h"
#include <termios.h>

int main(void)
{
    char        *unparsed_cmd;
    t_cmd_token *token_list;
    t_cmd_token *tmp;
    t_term      term;
    int         notnull;

    if (init_term(&term) == 0) /* initialise termcaps et. */
        if (config_term(&term) != 0)
            return -1;
    printf("$>");
    fflush(stdout);
    while (read(0, &term.last_char, 1) > 0)
    {
        //gestion du retour
        if ((term.last_char == 127 || term.last_char == 8) && term.ndx_cursor > 0)
        {
            term.str_cmd[term.ndx_cursor -1] = '\0';
            tputs(tgoto(term.caps.pos, term.ndx_cursor + 1, term.ndx_line), 1, ft_m_putchar);
            dprintf(1, " ");
            tputs(tgoto(term.caps.pos, term.ndx_cursor + 1, term.ndx_line), 1, ft_m_putchar);
            term.ndx_cursor--;
            continue;
        }
        //gestion des caracteres tapés
        else if (term.last_char != '\n' )
        {
            if (term.ndx_cursor >= STR_SIZE * term.nb_blocks)
            {
                term.str_cmd = resize_str(term.str_cmd, (term.nb_blocks + 1) * STR_SIZE);
                term.nb_blocks++;
            }
            term.str_cmd[term.ndx_cursor] = term.last_char;
            term.ndx_cursor++;
            tputs(tgoto(term.caps.pos, term.ndx_cursor + 1, term.ndx_line), 1, ft_m_putchar);
            dprintf(1, "%s", term.str_cmd + term.ndx_cursor - 1);
            continue;
        }
        if (term.str_cmd[0] != '\0' && term.last_char == '\n')
            dprintf(1, "\n");
        term.ndx_cursor = 0;
        term.ndx_line += 1;
        unparsed_cmd = term.str_cmd;
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
            term.ndx_line +=1;
        printf ("\n");
        printf ("$>");
        fflush(stdout);
        ft_memset(unparsed_cmd, '\0', term.nb_blocks * STR_SIZE);
    }
    if (tcsetattr(0, 0, &term.termios_backup) == -1)
          return (-1);
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
