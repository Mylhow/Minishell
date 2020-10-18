#include "../includes/terminal.h"

void    ctrl_up(t_term *term, t_block *block)
{
	if (term->ndx_cursor >= term->nb_cols - PROMPT_SIZE)
	{
		term->ndx_line--;
		block->delta_end_line++;
		term->ndx_cursor -= term->nb_cols;
		if (term->ndx_cursor < 0)
			term->ndx_cursor = 0;
		if (term->cursor_pos < PROMPT_SIZE && term->ndx_cursor < term->nb_cols - PROMPT_SIZE)
			term->cursor_pos = PROMPT_SIZE;
	}
}

void    ctrl_down(t_term *term, t_block *block)
{
	if (term->ndx_cursor + term->nb_cols < block->alloc_size)
	{
		term->ndx_line++;
		block->delta_end_line--;
		term->ndx_cursor += term->nb_cols;
		if (term->ndx_cursor > block->size)
		{
			term->ndx_cursor = block->size;
			term->cursor_pos = (block->size + PROMPT_SIZE) % term->nb_cols;
		}
	}
}

void    ctrl_left(t_term *term, t_block *block)
{
	(void)term;
	(void)block;	
}

void    ctrl_right(t_term *term, t_block *block)
{
	(void)term;
	(void)block;
}