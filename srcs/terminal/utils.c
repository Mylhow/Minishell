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
 ** TODO Check return term-fonction
*/

int		clear_eos(t_term *term, int original_line)
{
	int i;

	i = term->ndx_line;
	while (i > original_line)
	{
		put_cursor(0, i);
		put_caps(T_CLEOL, 0);
		i--;
	}
	term->ndx_line = term->original_line;
	put_cursor(term->cursor_pos, term->ndx_line);
	return (EXIT_SUCCESS);
}

/*
 ** TODO Attente d une description
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

/*
 ** TODO Fonction a supprimer lors du rendu
*/

void	debug(t_term *term)
{
	t_block	*block;
	int		tmp;

	tmp = 10;
	if (DEBUG)
	{
		block = (t_block *)(term->current_block)->value;
		put_caps(T_SAVE, 0);
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		put_caps(T_CLEOL, 0);
		if (term->last_char != '\n')
			ft_printf("%-18s = '%c' code:%d\n", "last_char",
				term->last_char, (int)term->last_char);
		else
			ft_printf("%-18s = '\\n' code:%d\n", "last_char",
				(int)term->last_char);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "ndx_cursor", term->ndx_cursor);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "ndx_line", term->ndx_line);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "nb_col", tgetnum(T_COLUMN));
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "nb_lines", tgetnum(T_LINE));
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "size", block->size);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %s\n", "str_cmd", block->str_cmd);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "nb_block", block->nb_blocks);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "original_line", term->original_line);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "cursor_pos", term->cursor_pos);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %d\n", "str_cmd_alloc_size", block->alloc_size - 1);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		ft_printf("%-18s = %s\n", "last_name_block", term->current_block->key);
		put_caps(T_RESTORE, 0);
	}
}
