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
	ft_printf("%s", ((t_block *)term->list_blocks->value)->str_cmd);
	term->cursor_pos = (((t_block *)term->list_blocks->value)->size +
			PROMPT_SIZE) % term->nb_cols;
	term->ndx_cursor = ((t_block *)term->list_blocks->value)->size;
	term->ndx_line += (((t_block *)term->list_blocks->value)->size +
			PROMPT_SIZE) / term->nb_cols;
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 ** Gere le mouvement du haut et affiche l'historique - 1
 ** Return [int] Status de reussite
 ** TODO Lorsque nous sommes sur plusieurs ligne '\n', ne pas supprimer commande
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
