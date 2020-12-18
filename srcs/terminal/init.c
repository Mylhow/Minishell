/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecaill <nlecaill@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:17 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 15:12:17 by nlecaill         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <unistd.h>
#include "libft_mem.h"
#include "libft_string.h"
#include "terminal.h"

/*
 ** Initialise les variables de la structure du terminal
 ** Return [int] Status de reussite
*/

static void	init_colors(t_term *term)
{
	term->colors[0] = 31;
	term->colors[1] = 32;
	term->colors[2] = 33;
	term->colors[3] = 34;
	term->colors[4] = 35;
	term->colors[5] = 36;
	term->colors[6] = 90;
	term->colors[7] = 91;
	term->colors[8] = 92;
	term->colors[9] = 93;
	term->colors[10] = 94;
	term->colors[11] = 95;
	term->colors[12] = 96;
	term->color = 0;
}

static int	init_term_variables(t_termios *termios)
{
	t_term	*term;
	t_block	*block;

	term = (*getterm());
	term->nb_cols = tigetnum(T_COLUMN);
	term->nb_lines = tigetnum(T_LINE);
	if (!(block = ft_blocknew()))
		return (EXIT_FAILURE);
	if (!(term->list_blocks = ft_hashnew("block_0", block)))
		return (EXIT_FAILURE);
	term->historic = NULL;
	term->current_block = term->list_blocks;
	term->current_historic = NULL;
	term->ndx_cursor = 0;
	term->cursor_pos = PROMPT_SIZE;
	term->ndx_line = 0;
	term->original_line = 0;
	term->last_char = '\0';
	term->esc_flag = 0;
	term->str_ccmd = 0;
	term->termios_backup = *termios;
	init_colors(term);
	return (EXIT_SUCCESS);
}

/*
 ** Initialise la structure du terminal
 ** Return [int] Status de reussite
*/

int			init_term(void)
{
	t_termios backup;

	tcgetattr(1, &backup);
	if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
		return (EXIT_FAILURE);
	if (init_term_variables(&backup) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (tigetflag("os") != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_CLEAR, 0) != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_RESET, 0) != 0)
		return (EXIT_FAILURE);
	if (tcgetattr(0, &(*getterm())->termios) == -1)
		return (EXIT_FAILURE);
	(*getterm())->termios.c_lflag &= ~(ICANON | VINTR | ECHO);
	if (tcsetattr(0, 0, &(*getterm())->termios) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
