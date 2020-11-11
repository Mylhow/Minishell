#include "libft_mem.h"

/*
 ** Vide la memoire et renvoie le status
 ** Return [int] Status
*/

int ft_exit(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	(void) env;
	wrdestroy();
	exit(0);
}