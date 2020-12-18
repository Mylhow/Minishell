/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:20 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:21 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft_string.h"

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
