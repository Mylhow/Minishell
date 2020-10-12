#include <term.h>
#include <unistd.h>
#include "libft.h"
#include "libft_mem.h"
#include "libft_string.h"
#include <stdio.h>
#include "../../includes/terminal.h"

static int init_term_variables(void)
{
	t_term *term;

	term = (*getTerm());
	term->nb_blocks = 1;
	term->ndx_cursor = 0;
	term->ndx_line = 0;
	term->ndx_str = 0;
	term->last_char = '\0';
	term->esc_flag = 0;
	if ((term->str_cmd = (char *)wrmalloc(STR_SIZE * term->nb_blocks)) == 0)
		return (EXIT_FAILURE);
	ft_bzero(term->str_cmd, STR_SIZE);
	return (EXIT_SUCCESS);
}

int init_term()
{
	if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
		return (EXIT_FAILURE);
	if (init_term_variables() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tigetflag("os") != 0)
		printf("os error\n");
	put_caps(T_CLEAR, 0);
	put_caps(T_RESET, 0);
	if (tcgetattr(0, &(*getTerm())->termios) == -1)
		return (EXIT_FAILURE);
	(*getTerm())->termios.c_lflag &= ~(ICANON);
	(*getTerm())->termios.c_lflag &= ~(ECHO);
	if (tcsetattr(0, 0, &(*getTerm())->termios) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}