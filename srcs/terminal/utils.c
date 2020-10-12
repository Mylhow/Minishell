#include <term.h>
#include <unistd.h>
#include <curses.h>
#include "libft_put.h"
#include "libft_string.h"
#include "../../includes/terminal.h"

int put_caps(char *caps, int color)
{
	int ret;
	char *caps_get;

	caps_get = tigetstr(caps);

	if (!(ft_strcmp(caps, T_FCOLOR)) || !(ft_strcmp(caps, T_BCOLOR)))
	{
		ret = tputs(tparm(caps_get, color), 1, putchar);
	}
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
