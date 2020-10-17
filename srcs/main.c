#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include "libft_mem.h"
#include "../includes/terminal.h"
#include "libft_printf.h"

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

static int update()
{
	printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getTerm())->last_char, 1) > 0)
	{
		if (!(handle_key()))
		{
			dprintf(1, "%s", ((t_block *)((*getTerm())->current_block)->value)->str_cmd);
			ft_hashclear(&((*getTerm())->list_blocks));
			if (!((*getTerm())->list_blocks = ft_hashnew("block_1", ft_blocknew())))
				return (ft_exit(EXIT_FAILURE));
			(*getTerm())->current_block = (*getTerm())->list_blocks;
			ft_printf("$ ");
			fflush(stdout);
			put_caps(T_CLEOL, 0);
			continue;
		}
		fflush(stdout);

	}
	return (EXIT_SUCCESS);
}

int main(int ac, char **av, char **environment)
{
	(void) ac;
	(void) av;
	(void) environment;

	if (!((*getTerm()) = wrmalloc(sizeof(t_term))))
		return (ft_exit(EXIT_FAILURE));
	if (init_term())
		return (ft_exit(EXIT_FAILURE));
	if (update())
		return (ft_exit(EXIT_FAILURE));
	if (tcsetattr(0, 0, &(*getTerm())->termios_backup) == -1)
		return (ft_exit(EXIT_FAILURE));
	return (ft_exit(EXIT_SUCCESS));
}