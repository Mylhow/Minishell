/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:24 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:25 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include <curses.h>
#include "libft_put.h"
#include "libft_string.h"
#include "libft_mem.h"
#include "terminal.h"
#include "libft_printf.h"

/*
 ** Execute un caps et lui donne la bonne couleur, si besoin.
 ** Return [int] Status de reussite
*/

int		put_caps(char *caps, int color)
{
	int		ret;
	char	*caps_get;

	caps_get = tigetstr(caps);
	if (!(ft_strcmp(caps, T_FCOLOR)) || !(ft_strcmp(caps, T_BCOLOR)))
		ret = tputs(tparm(caps_get, color), 1, putchar);
	else
	{
		(void)color;
		ret = tputs(caps_get, 1, ft_putchar_int);
	}
	return (ret);
}

/*
 ** Definie la position col, row du curseur
 ** Return [int] Status de reussite
*/

int		put_cursor(int col, int row)
{
	int		ret;
	char	*caps_get;

	caps_get = tigetstr(T_POS);
	ret = tputs(tgoto(caps_get, col, row), 1, ft_putchar_int);
	return (ret);
}

/*
 ** Alloue une nouvelle taille pour la chaine passe en parametre
 ** Return [*char] Pointeur sur la nouvelle chaine ou NULL
*/

char	*realloc_str(char *str, int new_size)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!(tmp = wrmalloc(new_size)))
		return (NULL);
	ft_bzero(tmp, new_size);
	while (str[++i])
		tmp[i] = str[i];
	wrfree(str);
	return (tmp);
}

/*
 ** Nettoie toutes les lignes utilise par la commande en cours d'ecriture
 ** Return [int] Status de reussite
*/

int		clear_eos(t_term *term, int original_line)
{
	int i;

	i = term->nb_lines - 1;
	while (i > original_line)
	{
		if (put_cursor(0, i) != 0)
			return (EXIT_FAILURE);
		if (put_caps(T_CLEOL, 0) != 0)
			return (EXIT_FAILURE);
		i--;
	}
	term->ndx_line = term->original_line;
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 ** Definie les positions exacte en fonction du curseur
 ** Return [void]
*/

void	get_pos(void)
{
	char	mychar;
	t_term	*term;

	term = (*getterm());
	mychar = '\0';
	write(1, "\e[6n", 4);
	term->ndx_line = 0;
	term->cursor_pos = 0;
	while (mychar != '[')
		read(STDIN_FILENO, &mychar, 1);
	while (read(STDIN_FILENO, &mychar, 1) && mychar != ';')
	{
		term->ndx_line *= 10;
		term->ndx_line += mychar - '0';
	}
	while (read(STDIN_FILENO, &mychar, 1) && mychar != 'R')
	{
		term->cursor_pos *= 10;
		term->cursor_pos += mychar - '0';
	}
	term->ndx_line--;
	term->cursor_pos--;
}
