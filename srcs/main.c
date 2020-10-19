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

static int new_cmd(t_term *term)
{
	char	 	*cmd;
	t_hash		*tmp;

	put_cursor(term->cursor_pos, term->ndx_line);
	if (!(cmd = ft_retcontent(term->list_blocks)))
		return (ft_exit(EXIT_FAILURE));
	ft_printf("%s\n", cmd);
	if (!(tmp = ft_hashnew("h", cmd)))
		return (ft_exit(EXIT_FAILURE));
	ft_hashadd_back(&term->historic, tmp);
	term->current_historic = NULL;
	ft_hashclear(&(term->list_blocks));
	if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
		return (ft_exit(EXIT_FAILURE));
	term->current_block = term->list_blocks;
	ft_printf("$ ");
	fflush(stdout);
	put_caps(T_CLEOL, 0);
	get_pos();
	return (EXIT_SUCCESS);
}
//TODO faire en sorte que les chaines de caracteres nulles ne s'écrive pas dans l'historique
static int update()
{
	t_term	*term;

	term = *getTerm();
	printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getTerm())->last_char, 1) > 0)
	{
		if (!(handle_key()))
		{
			if (new_cmd(term))
				return (ft_exit(EXIT_FAILURE));
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