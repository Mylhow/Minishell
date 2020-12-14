#include "libft_mem.h"
#include "terminal.h"
#include <ncurses.h>

/*
 ** Vide la memoire et renvoie le status
 ** Return [int] Status
*/

int ft_exit(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
    if (tcsetattr(1, 0, &(*getterm())->termios_backup) == -1)
        return 0;
    wrdestroy();
	exit(0);
}