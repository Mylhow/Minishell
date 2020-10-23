#include <term.h>
#include <unistd.h>
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_printf.h"
#include "../../includes/terminal.h"

static int init_term_variables(void)
{
	t_term *term;
	t_block *block;

	term = (*getTerm());
	term->nb_cols = tigetnum(T_COLUMN);
	term->nb_lines = tigetnum(T_LINE);
	if (!(block = ft_blocknew()))
		return (EXIT_FAILURE);
	term->list_blocks = ft_hashnew("block_1", block);
	term->historic = NULL;
	term->current_block = term->list_blocks;
	term->current_historic = NULL;
	term->ndx_cursor = 0;
	term->cursor_pos = PROMPT_SIZE;
	term->ndx_line = 0;
	term->original_line = 0;
	term->last_char = '\0';
	term->esc_flag = 0;
	return (EXIT_SUCCESS);
}

int init_term()
{
	if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
		return (EXIT_FAILURE);
	if (init_term_variables() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tigetflag("os") != 0)
		ft_printf("os error\n");
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