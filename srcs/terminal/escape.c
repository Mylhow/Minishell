#include "terminal.h"
#include "libft_printf.h"
#include "libft.h"
#include "libft_mem.h"
#include "libft_string.h"

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
		if (term->last_char == LEFTCHAR)
			move_left(block);
		else if (term->last_char == RIGHTCHAR)
			move_right(block);
		else if (term->last_char == UPCHAR)
			move_up(block);
		else if (term->last_char == DOWNCHAR)
			move_down(block);
		term->esc_flag = 0;
		return (2);
	}
	return (EXIT_SUCCESS);
}

int	backspace(t_block *block)
{
	t_term *term;
	char	*tmp;

	term = (*getTerm());
	if (block->ndx_str > 0)
	{
		tmp = ft_strdup(block->str_cmd);
		ft_bzero(block->str_cmd, block->ndx_str);
		ft_memcpy(block->str_cmd, tmp, term->ndx_cursor - 1);
		ft_strcat(block->str_cmd, tmp + term->ndx_cursor);
		put_cursor(term->ndx_cursor + PROMPT_SIZE - 1, term->ndx_line);
		put_caps(T_CLEOL, 0);
		ft_printf("%s", block->str_cmd + term->ndx_cursor - 1);
		block->ndx_str--;
		block->size--;
		term->ndx_cursor--;
		put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
	}
	return (EXIT_SUCCESS);
}
