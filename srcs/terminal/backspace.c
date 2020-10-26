#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_printf.h"

/*
 ** Realise les manipulations pour retirer une caractere
 ** Return [int] Status de reussite
*/

static int	backspace_process(t_term *term, t_block *block)
{
	char	*tmp;

	if (!(tmp = ft_strdup(block->str_cmd)))
		return (EXIT_FAILURE);
	ft_bzero(block->str_cmd, block->size);
	if (!(ft_memcpy(block->str_cmd, tmp, term->ndx_cursor)))
		return (EXIT_FAILURE);
	if (!(ft_strcat(block->str_cmd, tmp + term->ndx_cursor + 1)))
		return (EXIT_FAILURE);
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_CLEOL, 0) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

/*
 ** Permet de supprimer un caractere avec backspace
 ** Return [int] Status de reussite
*/

int			backspace(t_term *term, t_block *block)
{
	if (block->size > 0 && term->ndx_cursor > 0)
	{
		term->cursor_pos--;
		term->ndx_cursor--;
		if (backspace_process(term, block))
			return (EXIT_FAILURE);
		ft_printf("%s", block->str_cmd + term->ndx_cursor);
		block->size--;
		if (term->cursor_pos < 0)
		{
			term->cursor_pos = term->nb_cols - 1;
			term->ndx_line--;
		}
		if (put_caps(T_CLEOL, 0) != 0)
			return (EXIT_FAILURE);
	}
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
