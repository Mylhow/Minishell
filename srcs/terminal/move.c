#include "terminal.h"
#include "libft_string.h"
#include "libft_printf.h"

/*
 ** Gere le mouvement a droite et deplace le curseur a droite
 ** Return [void]
*/

void	move_right(t_block *block)
{
	t_term *term;

	term = (*getterm());
	if (term->ndx_cursor < block->size)
	{
		term->ndx_cursor++;
		term->cursor_pos++;
		if (term->cursor_pos == term->nb_cols)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
		}
	}
}

/*
 ** Gere le mouvement a gauche et deplace le curseur a gauche
 ** Return [void]
*/

void	move_left(void)
{
	t_term	*term;

	term = (*getterm());
	if (term->ndx_cursor > 0)
	{
		term->ndx_cursor--;
		term->cursor_pos--;
		if (term->cursor_pos < 0)
		{
			term->cursor_pos = term->nb_cols - 1;
			term->ndx_line--;
		}
	}
}

/*
 ** Gere le rendu de l'historique
 ** Return [int] Status de reussite
*/

int		print_historic(t_term *term, t_block *dup)
{
	if (!(term->list_blocks->value = ft_blockdup(dup)))
		return (EXIT_FAILURE);
	term->current_block = term->list_blocks;
	term->cursor_pos = PROMPT_SIZE;
	if (put_cursor(term->cursor_pos, term->original_line) != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_CLEOL, 0) != 0)
		return (EXIT_FAILURE);
	if (clear_eos(term, term->original_line))
		return (EXIT_FAILURE);
	t_block *mBlock = term->list_blocks->value;
	ft_printf("%s", mBlock->str_cmd);
	mBlock->nb_blocks = (mBlock->size + PROMPT_SIZE) / term->nb_cols + 1;
	term->cursor_pos = (mBlock->size + PROMPT_SIZE) % term->nb_cols;
	term->ndx_cursor = mBlock->size;
	term->ndx_line = term->original_line + (mBlock->nb_blocks - 1);
	if (term->ndx_line > term->nb_lines - 1)
	{
		term->ndx_line = term->nb_lines - 1;
		term->original_line = term->ndx_line - (mBlock->nb_blocks - 1);
	}
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 ** Gere le mouvement du haut et affiche l'historique - 1
 ** Return [int] Status de reussite
*/

int		move_up(t_term *term)
{
	int		flag;

	flag = 0;
	if (!term->historic)
		return (EXIT_SUCCESS);
	else if (!term->current_historic)
	{
		if ((term->current_historic = term->historic->last(term->historic)))
			flag = 1;
	}
	else if (term->current_historic->before)
	{
		term->current_historic = term->current_historic->before;
		flag = 1;
	}
	if (flag)
		return (print_historic(term, (t_block *)term->current_historic->value));
	return (EXIT_SUCCESS);
}

/*
 ** Gere le mouvement du bas et affiche l'historique + 1 ou rien
 ** Return [int] Status de reussite
*/

int		move_down(t_term *term)
{
	if (!term->historic)
		return (EXIT_SUCCESS);
	else if (term->current_historic && term->current_historic->next)
	{
		term->current_historic = term->current_historic->next;
		return (print_historic(term, (t_block *)term->current_historic->value));
	}
	else if (term->current_historic && !(term->current_historic->next))
	{
		term->current_historic = NULL;
		if (!(term->list_blocks->value = ft_blocknew()))
			return (EXIT_FAILURE);
		return (print_historic(term, (t_block *)term->list_blocks->value));
	}
	return (EXIT_SUCCESS);
}
