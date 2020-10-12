#include <term.h>
#include <unistd.h>
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
    tmp = wrmalloc(new_size);
    ft_bzero(tmp, new_size);
    while (str[++i])
        tmp[i] = str[i];
    wrfree(str);
    return (tmp);
}

void    debug(t_term *term)
{
    int tmp;

    tmp = 3;
    put_caps(T_SAVE, 0);
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "last_char ='%c' code:%d    \n", term->last_char, (int)term->last_char);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "ndx_cursor =%d    \n", term->ndx_cursor);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "ndx_line =%d    \n", term->ndx_line);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "ndx_str=%d    \n", term->ndx_str);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "str_cmd = %s    \n", term->str_cmd);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "str_cmd_size =%d    \n", term->str_size);
    tmp ++;
    put_cursor(2 * tgetnum(T_COLUMN) / 4, tmp);
    dprintf(1, "str_cmd_alloc_size =%d    \n", term->nb_blocks * STR_SIZE);
    put_caps(T_RESTORE, 0);
}