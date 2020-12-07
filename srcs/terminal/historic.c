#include "libft_printf.h"
#include "terminal.h"
#include "libft_ctype.h"

int ft_histo_add(t_term *term, void *value)
{
	t_hash *tmp;

	if (!(tmp = ft_hashnew("h", value)))
		return (EXIT_FAILURE);
	ft_hashadd_back(&term->historic, tmp);
	return (EXIT_SUCCESS);
}

/*
 ** Gere le rendu de l'historique
 ** Return [int] Status de reussite
*/

int		print_historic(t_term *term, t_block *dup)
{
	t_block *block;

	if (!(term->list_blocks->value = ft_blockdup(dup)))
		return (EXIT_FAILURE);
	term->current_block = term->list_blocks;
	term->cursor_pos = PROMPT_SIZE;
	if (put_cursor(term->cursor_pos, term->original_line) != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_CLEOL, 0) != 0 && clear_eos(term, term->original_line))
		return (EXIT_FAILURE);
	block = term->list_blocks->value;
	ft_printf("%s", block->str_cmd);
	block->nb_blocks = (block->size + PROMPT_SIZE) / term->nb_cols + 1;
	term->cursor_pos = (block->size + PROMPT_SIZE) % term->nb_cols;
	term->ndx_cursor = block->size;
	term->ndx_line = term->original_line + (block->nb_blocks - 1);
	if (term->ndx_line > term->nb_lines - 1)
	{
		term->ndx_line = term->nb_lines - 1;
		term->original_line = term->ndx_line - (block->nb_blocks - 1);
	}
	return (EXIT_SUCCESS);
}