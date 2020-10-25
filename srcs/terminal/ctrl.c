#include "terminal.h"
#include "libft_ctype.h"

/*
 ** Gere le mouvement du CTRL+haut et remonte dans une multi-ligne
 ** Return [void]
*/

void	ctrl_up(t_term *term)
{
	if (term->ndx_cursor >= term->nb_cols - PROMPT_SIZE)
	{
		term->ndx_line--;
		term->ndx_cursor -= term->nb_cols;
		if (term->ndx_cursor < 0)
			term->ndx_cursor = 0;
		if (term->cursor_pos < PROMPT_SIZE
		&& term->ndx_cursor < term->nb_cols - PROMPT_SIZE)
			term->cursor_pos = PROMPT_SIZE;
	}
}

/*
 ** Gere le mouvement du CTRL+bas et descend dans une multi-ligne
*/

void	ctrl_down(t_term *term, t_block *block)
{
	if (term->ndx_cursor + term->nb_cols < block->alloc_size)
	{
		term->ndx_line++;
		term->ndx_cursor += term->nb_cols;
		if (term->ndx_cursor > block->size)
		{
			term->ndx_cursor = block->size;
			term->cursor_pos = (block->size + PROMPT_SIZE) % term->nb_cols;
		}
	}
}

/*
 ** Gere le mouvement du CTRL+gauche et deplace le curseur au mot precedent
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

int		ctrl_left(t_term *term, t_block *block)
{
	while (ft_isspace(block->str_cmd[term->ndx_cursor - 1]))
	{
		if (term->cursor_pos % term->nb_cols == 0 && term->ndx_cursor != 0
		&& term->ndx_line > 0)
		{
			term->cursor_pos = term->nb_cols;
			term->ndx_line--;
		}
		term->ndx_cursor--;
		term->cursor_pos--;
	}
	while (block->str_cmd[term->ndx_cursor - 1] >= '!'
	&& block->str_cmd[term->ndx_cursor - 1] <= '~')
	{
		if (term->cursor_pos % term->nb_cols == 0 && term->ndx_cursor != 0
		&& term->ndx_line > 0)
		{
			term->cursor_pos = term->nb_cols;
			term->ndx_line--;
		}
		term->ndx_cursor--;
		term->cursor_pos--;
	}
	(term->cursor_pos < PROMPT_SIZE) ? term->cursor_pos = PROMPT_SIZE : 0;
	put_cursor(term->cursor_pos, term->ndx_line);
	return (EXIT_SUCCESS);
}

/*
 ** Gere le mouvement du CTRL+droite et deplace le curseur au prochain mot
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

int		ctrl_right(t_term *term, t_block *block)
{
	while (ft_isspace(block->str_cmd[term->ndx_cursor]))
	{
		if (term->cursor_pos % term->nb_cols == 0 && term->ndx_cursor != 0)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
		}
		term->ndx_cursor++;
		term->cursor_pos++;
	}
	while (block->str_cmd[term->ndx_cursor] >= '!'
	&& block->str_cmd[term->ndx_cursor] <= '~')
	{
		if (term->cursor_pos % term->nb_cols == 0 && term->ndx_cursor != 0)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
		}
		term->ndx_cursor++;
		term->cursor_pos++;
	}
	put_cursor(term->cursor_pos, term->ndx_line);
	return (EXIT_SUCCESS);
}
