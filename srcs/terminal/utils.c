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

	caps_get = tigetstr("cup");
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

static void freedebug(t_term *term)
{
	t_block *block;
	int tmp;

	tmp = 3;
	block = (t_block *)term->list_blocks->last(term->list_blocks)->value;
	put_caps(T_SAVE, 0);
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	tmp ++;
	put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
	dprintf(1, "%-100s\n", " ");
	put_caps(T_RESTORE, 0);
}

void    debug(t_term *term)
{
	t_block *block;
    int tmp;

    tmp = 3;
    if (0) {
		freedebug(term);
		block = (t_block *) (term->current_block)->value;
		put_caps(T_SAVE, 0);
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = '%c' code:%d    \n", "last_char", term->last_char, (int) term->last_char);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "ndx_cursor", term->ndx_cursor);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "ndx_line", term->ndx_line);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "ndx_str", block->ndx_str);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %s\n", "str_cmd", block->str_cmd);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "str_cmd_size", block->size);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "nb_block", block->nb_blocks);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %d\n", "str_cmd_alloc_size", block->nb_blocks * STR_SIZE);
		tmp++;
		put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
		dprintf(1, "%-18s = %s\n", "last_name_block", term->current_block->key);
		put_caps(T_RESTORE, 0);
	}
}