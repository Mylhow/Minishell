/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:21 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:22 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_printf.h"
#include "syntax_error.h"
#include "expander.h"
#include "sh_utils.h"

/*
 ** Check, si des opérateurs sont dans la chaine de la commande
 ** Return [int] Status de reussite
*/

static int	ft_checkop(t_term *term)
{
	int		i;
	int		max;
	t_block *current;

	current = (t_block *)term->current_block->value;
	max = ft_strlen(current->str_cmd);
	i = max;
	while (current->str_cmd[i]
	&& !ft_charstr(current->str_cmd[i], "\t "))
		i--;
	i--;
	return (ft_charstr(current->str_cmd[i], "&|<>()"));
}

/*
** Check la syntax de chaque ligne et renvoie un code basé sur syntax_error
** Return [int] 0 - Success (Exit_success)
** Return [int] 1 - Failure (Exit_failure)
** Return [int] 3 - Ask new command (New_command)
** Return [int] 4 - Ask new command on syntax_error (Ncmd_syntax_error)
*/

static int	ft_checksyntax(t_term *term, int flagantislash)
{
	int	ret;
	int index;
	int len;

	ret = syntax_error(term->str_ccmd, flagantislash);
	if (ret == NEW_LINE)
		return (ft_newline(term));
	if (ret == NLINE_COMMA)
	{
		len = ft_strlen(((t_block *)term->current_block->value)->str_cmd);
		index = ft_checkop(term);
		if (index)
		{
			((t_block *)term->current_block->value)->str_cmd[len] = ';';
			((t_block *)term->current_block->value)->str_cmd[len + 1] = ' ';
			((t_block *)term->current_block->value)->size += 2;
		}
		else
			((t_block *)term->current_block->value)->str_cmd[len] = ' ';
		return (ft_newline(term));
	}
	return (ret);
}

/*
 ** Manage toutes les touches tape
 ** Return [int] Status de reussite
*/

static int	check_key(t_term *term, t_block *block)
{
	if (term->last_char == '\033' || term->esc_flag != 0)
		return (escape_sequences(term, block));
	if (term->last_char == DELCHAR || term->last_char == BACKSPACE)
		return (!backspace(term, block));
	if (term->last_char != '\n' && term->last_char != _EOF)
	{
		if (insert(term, block))
			return (EXIT_FAILURE);
		return (PROCESS_SUCCESS);
	}
	else if (term->last_char == '\n')
	{
		if (term->str_ccmd)
			wrfree(term->str_ccmd);
		if (!(term->str_ccmd = ft_strjoinblock(term->list_blocks)))
			return (EXIT_FAILURE);
		if (block->str_cmd[ft_strlen(block->str_cmd) - 1] == '\\' && !is_escaped(block->str_cmd, ft_strlen(block->str_cmd) - 1))
		{
			block->str_cmd[ft_strlen(block->str_cmd) - 1] = '\0';
			block->size--;
			return (ft_checksyntax(term, 1));
		}
		return (ft_checksyntax(term, 0));
	}
	return (EXIT_FAILURE);
}

/*
** Manage le key control
** Return [int] Status de reussite
*/

int			handle_key(void)
{
	t_term	*term;
	t_block *block;
	int		ret;

	term = (*getterm());
	term->nb_cols = tigetnum(T_COLUMN);
	block = (t_block *)(ft_hashlast(term->list_blocks)->value);
	ret = check_key(term, block);
	if (ret == PROCESS_SUCCESS || ret == EXIT_FAILURE)
		return (ret);
	term->ndx_line = term->ndx_line + 1;
	if (term->ndx_line > term->nb_lines)
	{
		term->ndx_line = term->nb_lines;
		term->original_line = term->ndx_line - (block->nb_blocks - 1);
	}
	(term->last_char == '\n') ? ft_printf("\n") : 0;
	term->ndx_cursor = 0;
	term->cursor_pos = 0;
	if (ret == NCMD_SYNTAX_ERROR)
		g_exit_status = 1;
	return (ret);
}
