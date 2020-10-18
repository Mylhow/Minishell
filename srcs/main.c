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

void get_pos()
{
	char	mychar;
	t_term	*term;

	term = (*getTerm());
	mychar = '\0';
	write(1, "\e[6n", 4);
	term->ndx_line = 0;
	term->cursor_pos = 0;
	while(mychar != '[')
		read(STDIN_FILENO, &mychar, 1);
	while(read(STDIN_FILENO, &mychar, 1) && mychar != ';')
	{
		term->ndx_line *= 10;
		term->ndx_line += mychar - '0';
	}
	while(read(STDIN_FILENO, &mychar, 1) && mychar != 'R')
	{
		term->cursor_pos *= 10;
		term->cursor_pos += mychar - '0';
	}
	term->ndx_line--;
	term->cursor_pos--;
}

static int update()
{
	t_term *term;

	term = *getTerm();
	printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getTerm())->last_char, 1) > 0)
	{
		if (!(handle_key()))
		{
			put_cursor(term->cursor_pos, term->ndx_line);
			dprintf(1, "%s\n", ((t_block *)((*getTerm())->current_block)->value)->str_cmd); //debug
			ft_hashclear(&((*getTerm())->list_blocks));
			if (!((*getTerm())->list_blocks = ft_hashnew("block_1", ft_blocknew())))
				return (ft_exit(EXIT_FAILURE));
			(*getTerm())->current_block = (*getTerm())->list_blocks;
			ft_printf("$ ");
			fflush(stdout);
			put_caps(T_CLEOL, 0);
			get_pos();
			// debug(*getTerm());
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