/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:15 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:16 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft_ctype.h"

/*
 ** Gere le mouvement du CTRL+gauche et deplace le curseur au mot precedent
 ** Return [void]
*/

void		ctrl_left(t_term *term, t_block *block)
{
	while (ft_isspace(block->str_cmd[term->ndx_cursor - 1]))
	{
		if ((term->cursor_pos % term->nb_cols == 0) && term->ndx_cursor != 0
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
		if ((term->cursor_pos % term->nb_cols == 0) && term->ndx_cursor != 0
			&& term->ndx_line > 0)
		{
			term->cursor_pos = term->nb_cols;
			term->ndx_line--;
		}
		term->ndx_cursor--;
		term->cursor_pos--;
	}
}

/*
 ** Gere le mouvement du CTRL+droite et deplace le curseur au prochain mot
 ** Return [void]
*/

void		ctrl_right(t_term *term, t_block *block)
{
	while (ft_isspace(block->str_cmd[term->ndx_cursor]))
	{
		if ((term->cursor_pos % term->nb_cols == 0) && term->ndx_cursor != 0)
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
		if ((term->cursor_pos % term->nb_cols == 0) && term->ndx_cursor != 0)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
		}
		term->ndx_cursor++;
		term->cursor_pos++;
	}
}

/*
 ** Gere le mouvement du CTRL+haut et remonte dans une multi-ligne
 ** Return [void]
*/

void		ctrl_up(t_term *term)
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
 ** Return [void]
*/

void		ctrl_down(t_term *term, t_block *block)
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
