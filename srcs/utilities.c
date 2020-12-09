#include "terminal.h"
#include "env.h"

/*
 ** Renvoie un pointeur sur la structure du terminal
 ** Return [**t_term] structure du terminal
*/

t_term		**getterm(void)
{
	static t_term *term;

	return (&term);
}

