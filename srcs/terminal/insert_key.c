#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_printf.h"

/*
 ** Deplace le curseur, si ont depasse le nombre de colonne
 ** Return [void]
*/

static void	new_line(t_term *term)
{
	if (term->cursor_pos == term->nb_cols)
	{
		ft_printf("\n");
		term->ndx_line++;
		term->cursor_pos = 0;
		if (term->ndx_line > term->nb_lines - 1)
		{
			term->original_line -= term->ndx_line - (term->nb_lines - 1);
			term->ndx_line = term->nb_lines - 1;
		}
	}
	else if ((term->cursor_pos +
	(((t_block *)term->current_block->value)->size - term->ndx_cursor))
	> term->nb_cols)
	{
		if (term->original_line +
		((t_block *)term->current_block->value)->nb_blocks - 1
		> term->nb_lines - 1)
		{
			term->original_line -= 1;
			term->ndx_line -= 1;
			put_cursor(term->cursor_pos, term->ndx_line);
		}
	}
}

/*
 ** Ajoute une touche dans la chaine a n importe quel endroit
 ** Return [int] Status de reussite
*/

static int	insert_key(t_term *term, t_block *block)
{
	char	*tmp;

	if (term->ndx_cursor < block->size)
	{
		if (!(tmp = ft_strdup(block->str_cmd)))
			return (EXIT_FAILURE);
		ft_bzero(block->str_cmd, block->size);
		if (!(ft_memcpy(block->str_cmd, tmp, term->ndx_cursor)))
			return (EXIT_FAILURE);
		block->str_cmd[term->ndx_cursor] = term->last_char;
		if (!(ft_strcat(block->str_cmd, tmp + term->ndx_cursor)))
			return (EXIT_FAILURE);
		if (put_caps(T_CLEOL, 0) != 0)
			return (EXIT_FAILURE);
		ft_printf("%s", block->str_cmd + term->ndx_cursor);
	}
	else
	{
		block->str_cmd[block->size] = term->last_char;
		ft_printf("%s", block->str_cmd + block->size);
	}
	return (EXIT_SUCCESS);
}

/*
 ** Insert un caractere dans le block
 ** Return [int] Status de reussite
*/

int			insert(t_block *block)
{
	t_term	*term;

	term = (*getterm());
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	if (block->size == block->alloc_size - 1)
	{
		block->nb_blocks++;
		block->alloc_size += term->nb_cols;
		if (!(block->str_cmd = realloc_str(block->str_cmd, block->alloc_size)))
			return (EXIT_FAILURE);
	}
	if (insert_key(term, block))
		return (EXIT_FAILURE);
	term->ndx_cursor++;
	term->cursor_pos++;
	block->size++;
	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	new_line(term);
	return (EXIT_SUCCESS);
}
