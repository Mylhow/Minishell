#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include "terminal.h"
#include "libft_mem.h"
#include "libft_printf.h"
#include "libft_string.h"

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
	t_block		*copy;
	t_hash		*tmp;

	if (!(copy = ft_blockhashdup(term->list_blocks)))
		return (ft_exit(EXIT_FAILURE));
	if (ft_strlen(copy->str_cmd) != 0)
	{
		if (!(tmp = ft_hashnew("h", copy)))
			return (ft_exit(EXIT_FAILURE));
		ft_hashadd_back(&term->historic, tmp);
		term->current_historic = NULL;
		ft_printf("%s\n", copy->str_cmd); //TODO: Rendu debug
		ft_hashclear(&(term->list_blocks));
		if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
			return (ft_exit(EXIT_FAILURE));
		term->current_block = term->list_blocks;
		term->original_line = term->ndx_line + (copy->size / term->nb_cols) + 1; //TODO: Calcul a changer, en fonction du nombre de ligne prompt
	}
	else
	{
		term->ndx_line--;
		term->cursor_pos = 0;
	}
	return (EXIT_SUCCESS);
}

static int update()
{
	t_term	*term;

	term = *getTerm();
	ft_printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getTerm())->last_char, 1) > 0)
	{
		if (!(handle_key()))
		{
			if (new_cmd(term))
				return (ft_exit(EXIT_FAILURE));
			ft_printf("$ ");
			fflush(stdout);
			put_caps(T_CLEOL, 0);
			get_pos();
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