#include "libft_printf.h"
#include "terminal.h"
#include "libft_ctype.h"

int ft_histo_add(t_term *term, char *key, void *value)
{
	t_hash *tmp;

	if (!value)
		return PROCESS_SUCCESS;
	if (!(tmp = ft_hashnew(key, value)))
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

	if (!(term->current_block->value = ft_blockdup(dup)))
		return (EXIT_FAILURE);
	block = term->current_block->value;
	term->cursor_pos = PROMPT_SIZE;
	if (put_cursor(term->cursor_pos, term->original_line) != 0)
		return (EXIT_FAILURE);
	if (put_caps(T_CLEOL, 0) != 0)
		return (EXIT_FAILURE);
	if (clear_eos(term, term->original_line))
		return (EXIT_FAILURE);
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