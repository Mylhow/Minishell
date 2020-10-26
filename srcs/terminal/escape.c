#include "terminal.h"
#include "libft_mem.h"
#include <unistd.h>

/*
 ** Manage les mouvements curseur (ctrl, move)
 ** Return [int] Status de reussite
*/

static int	movement_manage(t_term *term, t_block *block)
{
	char my_char;

	if (term->esc_flag == 2)
	{
		if (term->last_char == '1')
			term->esc_flag = 3;
		else
		{
			if (move_manage(term, block))
				return (EXIT_FAILURE);
		}
		return (PROCESS_SUCCESS);
	}
	else if (term->esc_flag == 3)
	{
		read(STDIN_FILENO, &my_char, 1);
		//TODO 2 pour mac 5 pour linux
		if (my_char == '2')
		{
			read(STDIN_FILENO, &my_char, 1);
			if (ctrl_manage(term, block, my_char))
				return (EXIT_FAILURE);
			return (PROCESS_SUCCESS);
		}
	}
	return (EXIT_SUCCESS);
}

/*
 ** Manage les sequences des fleches
 ** Return [int] Status de reussite
*/

int			move_manage(t_term *term, t_block *block)
{
	if (term->last_char == LEFTCHAR)
		move_left();
	else if (term->last_char == RIGHTCHAR)
		move_right(block);
	else if (term->last_char == UPCHAR && move_up(term))
		return (EXIT_FAILURE);
	else if (term->last_char == DOWNCHAR && move_down(term))
		return (EXIT_FAILURE);
	else if (term->last_char == HOMECHAR)
	{
		term->ndx_line = term->original_line;
		term->ndx_cursor = 0;
		term->cursor_pos = PROMPT_SIZE;
	}
	else if (term->last_char == ENDCHAR)
	{
		term->ndx_line = (block->size / term->nb_cols) + term->original_line;
		term->ndx_cursor = block->size;
		term->cursor_pos = block->size % term->nb_cols + PROMPT_SIZE;
	}
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	term->esc_flag = 0;
	return (EXIT_SUCCESS);
}

/*
 ** Manage les sequences CTRL
 ** Return [int] Statue de reussite
*/

int			ctrl_manage(t_term *term, t_block *block, char my_char)
{
	if (my_char == 'A')
		ctrl_up(term);
	else if (my_char == 'B')
		ctrl_down(term, block);
	else if (my_char == 'C')
		ctrl_right(term, block);
	else if (my_char == 'D')
		ctrl_left(term, block);
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	term->esc_flag = 0;
	return (EXIT_SUCCESS);
}

/*
 ** Manage la sequence d'echappement
 ** Return [int] Status de reussite
*/

int			escape_sequences(t_term *term, t_block *block)
{
	if (term->last_char == '\033')
	{
		term->esc_flag = 1;
		return (PROCESS_SUCCESS);
	}
	else if (term->esc_flag == 1 && term->last_char == '[')
	{
		term->esc_flag = 2;
		return (PROCESS_SUCCESS);
	}
	else if (term->esc_flag >= 2)
	{
		if (movement_manage(term, block))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
