#include "terminal.h"

void     move_right(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->ndx_cursor < block->size)
	{
		term->ndx_cursor++;
		term->cursor_pos++;
		if (term->cursor_pos == term->nb_cols)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
			block->delta_end_line--;
		}
	}
}

void     move_left(t_block *block)
{
    t_term *term;

    term = (*getTerm());
	if (term->ndx_cursor > 0)
	{
    	term->ndx_cursor--;
		term->cursor_pos--;
		if (term->cursor_pos < 0)
		{
			term->cursor_pos = term->nb_cols - 1;
			term->ndx_line--;
			block->delta_end_line++;
		}
	}
}
#include "libft_string.h"
#include "libft_printf.h"
int     move_up(t_term *term, t_block *block)
{
	char	*current;
	int		flag;

	flag = 0;
	if (!term->current_historic)
	{
		if ((term->current_historic = term->historic->last(term->historic)))
		{
			flag = 1;
		}
	}
	else if (term->current_historic->before)
	{
		term->current_historic = term->current_historic->before;
		flag = 1;
	}
	if (flag)
	{
		current = (char *)term->current_historic->value;
		put_cursor(PROMPT_SIZE, term->ndx_line);
		put_caps(T_CLEOL, 0);
		block->size = ft_strlen(current);
		block->nb_blocks = block->size / term->nb_cols + 1;
		if (!(block->str_cmd = ft_strdup(current)))
			return (EXIT_FAILURE);
		block->alloc_size = term->nb_cols * block->nb_blocks + 1 - PROMPT_SIZE;
		ft_printf("%s", current);
		term->cursor_pos = block->size + PROMPT_SIZE;
		term->ndx_cursor = block->size;
		put_cursor(term->cursor_pos, term->ndx_line);
	}
	return (EXIT_SUCCESS);
}

void     move_down(t_block *block)
{
	(void)block;
}
