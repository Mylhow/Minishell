#include <term.h>
#include <curses.h>
#include "libft_put.h"
#include "libft_string.h"
#include "libft_mem.h"
#include "../../includes/terminal.h"

int put_caps(char *caps, int color)
{
	int ret;
	char *caps_get;

	caps_get = tigetstr(caps);

	if (!(ft_strcmp(caps, T_FCOLOR)) || !(ft_strcmp(caps, T_BCOLOR)))
		ret = tputs(tparm(caps_get, color), 1, putchar);
	else
	{
		(void) color;
		ret = tputs(caps_get, 1, ft_putchar_int);
	}
	return (ret);
}

int put_cursor(int col, int row)
{
	int ret;
	char *caps_get;

	caps_get = tigetstr(T_POS);
	ret = tputs(tgoto(caps_get, col, row), 1, ft_putchar_int);
	return (ret);
}

char *realloc_str(char *str, int new_size)
{
    char    *tmp;
    int     i;

    i = -1;
    if (!(tmp = wrmalloc(new_size)))
    	return (0);
    ft_bzero(tmp, new_size);
    while (str[++i])
        tmp[i] = str[i];
    wrfree(str);
    return (tmp);
}

void get_pos()
{
	char	mychar;
	t_term	*term;

	term = (*getTerm());
	mychar = '\0';
	write(1, "\e[6n", 4);
	term->ndx_line = 0;
	term->cursor_pos = 0;
	while(mychar != '[')
		read(STDIN_FILENO, &mychar, 1);
	while(read(STDIN_FILENO, &mychar, 1) && mychar != ';')
	{
		term->ndx_line *= 10;
		term->ndx_line += mychar - '0';
	}
	while(read(STDIN_FILENO, &mychar, 1) && mychar != 'R')
	{
		term->cursor_pos *= 10;
		term->cursor_pos += mychar - '0';
	}
	term->ndx_line--;
	term->cursor_pos--;
}

void    debug(t_term *term)
{
	t_block *block;
    int tmp;

    tmp = 3;
    if (1) {
		block = (t_block *) (term->current_block)->value;
		put_caps(T_SAVE, 0);
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = '%c' code:%d\n", "last_char", term->last_char, (int) term->last_char);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "ndx_cursor", term->ndx_cursor);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "ndx_line", term->ndx_line);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "nb_col", tgetnum(T_COLUMN));
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "size", block->size);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %s\n", "str_cmd", block->str_cmd);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "nb_block", block->nb_blocks);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "delta_line", block->delta_end_line);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "cursor_pos", term->cursor_pos);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %d\n", "str_cmd_alloc_size", block->alloc_size);
		tmp++;
		put_cursor(term->nb_cols / 2, tmp);
		put_caps(T_CLEOL, 0);
		dprintf(1, "%-18s = %s\n", "last_name_block", term->current_block->key);
		put_caps(T_RESTORE, 0);
	}
}