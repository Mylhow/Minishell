#include "terminal.h"
#include "libft_printf.h"
#include "libft.h"
#include "libft_mem.h"
#include "libft_string.h"

static void move_manage(t_term *term, t_block *block)
{
	if (term->last_char == LEFTCHAR)
		move_left(block);
	else if (term->last_char == RIGHTCHAR)
		move_right(block);
	else if (term->last_char == UPCHAR)
		move_up(block);
	else if (term->last_char == DOWNCHAR)
		move_down(block);
	else if (term->last_char == HOMECHAR)
		term->ndx_cursor = 0;
	else if (term->last_char == ENDCHAR)
		term->ndx_cursor = block->size;
	put_cursor(term->cursor_pos, term->ndx_line);
	term->esc_flag = 0;
}

int	escape_sequences(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->last_char == '\033') {
		term->esc_flag = 1;
		return (2);
	}
	else if (term->esc_flag == 1 && term->last_char == '[')
	{
		term->esc_flag = 2;
		return (2);
	}
	else if (term->esc_flag == 2)
	{
		move_manage(term, block);
		return (2);
	}
	return (EXIT_SUCCESS);
}

int	backspace(t_block *block)
{
	t_term *term;
	char	*tmp;

	term = (*getTerm());
	if (block->size > 0 && term->ndx_cursor > 0)
	{
		tmp = ft_strdup(block->str_cmd);
		ft_bzero(block->str_cmd, block->size);
		ft_memcpy(block->str_cmd, tmp, term->ndx_cursor - 1);
		ft_strcat(block->str_cmd, tmp + term->ndx_cursor);
		put_cursor(term->cursor_pos - 1, term->ndx_line);
		put_caps(T_CLEOL, 0);
		ft_printf("%s", block->str_cmd + term->ndx_cursor - 1);
		block->size--;
		term->ndx_cursor--;
		term->cursor_pos--;
		if (term->cursor_pos == PROMPT_SIZE)
		{
			term->cursor_pos = term->nb_cols;
			term->ndx_line--;
		}
		put_cursor(term->cursor_pos, term->ndx_line);
	}
	return (EXIT_SUCCESS);
}
