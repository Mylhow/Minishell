#include "terminal.h"

void     move_right(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->ndx_cursor < block->size)
		term->ndx_cursor++;
}

void     move_left(t_block *block)
{
    t_term *term;

    term = (*getTerm());
	(void)block;
    if (term->ndx_cursor > 0)
    	term->ndx_cursor--;
}

void     move_up(t_block *block)
{
    t_term *term;

    term = (*getTerm());
    if (term->current_block->before)
    {
    	term->current_block = term->current_block->before;
    	block = term->current_block->value;
		if (term->ndx_cursor > block->size)
			term->ndx_cursor = block->size;
        term->ndx_line -= 1;
    }
}

void     move_down(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->current_block->next)
	{
		term->current_block = term->current_block->next;
		block = term->current_block->value;
		if (term->ndx_cursor > block->size)
			term->ndx_cursor = block->size;
		term->ndx_line += 1;
	}
}
