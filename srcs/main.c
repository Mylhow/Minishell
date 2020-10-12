#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "libft_mem.h"
#include "libft_string.h"
#include "../includes/terminal.h"

int ft_exit(int exit_status)
{
	wrdestroy();
	return (exit_status);
}

t_term **getTerm(void)
{
	static t_term *term;

	return (&term);
}

int main(int ac, char **av, char **environment)
{
	(void) ac;
	(void) av;
	(void) environment;

	if (!((*getTerm()) = wrmalloc(sizeof(t_term))))
		return (ft_exit(EXIT_FAILURE));
	if (init_term() == EXIT_FAILURE)
		return (ft_exit(EXIT_FAILURE));
	printf("$>");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getTerm())->last_char, 1) > 0)
	{
	    if (!(handle_key()))
            continue;
		//printf("\n");
		//printf("$>");
		fflush(stdout);
		ft_bzero((*getTerm())->str_cmd, (*getTerm())->nb_blocks * STR_SIZE);
	}
	if (tcsetattr(0, 0, &(*getTerm())->termios_backup) == -1)
		return (ft_exit(EXIT_FAILURE));
	return (ft_exit(EXIT_SUCCESS));
}