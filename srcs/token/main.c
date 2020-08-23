#include "minishell.h"
#include "libft_gnl.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(int ac, char **av, char **environnement)
{
    t_term      term;
	envir       *env;

    if (!(env = init_env(ac, av, environnement)))
        return -1;
    if (init_term(&term) == 0) /* initialise termcaps et. */
        if (config_term(&term) != 0)
            return -1;
    printf("$>");
    fflush(stdout); 
    while (read(0, &term.last_char, 1) > 0)
    {
        if (handle_key(&term))
            continue;
        main_token(&term);
        printf ("\n");
        // printf ("$>%d, %d, %d", term.ndx_line, term.ndx_cursor, term.ndx_str);
        // printf("$>\033[1D\033[K");
        printf("$>");
        fflush(stdout);
        ft_memset(term.str_cmd, '\0', term.nb_blocks * STR_SIZE);
    }
    //exit terminal properly
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
