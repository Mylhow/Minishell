#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_number.h"
#include "libft_printf.h"

/*
 ** Imprime les espaces pour une tabulation (4 espaces)
 ** Return [int] Status de reussite
*/

static int	ft_tabulation(t_term *term, t_block *block)
{
	int i;

	i = -1;
	term->last_char = ' ';
	while (++i < 4)
	{
		if (insert(block))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/*
 ** Gere le \n dans le block. Ajoute un block dans la structure.
 ** Return [int] Status de reussite
*/

static int	ft_return_line(t_term *term, t_block *block)
{
	t_hash	*hash;

	if (block->str_cmd[block->size - 1] == '\\')
	{
		if (!(hash = ft_hashnew(ft_strjoin("block_",
					ft_itoa(ft_hashlen(term->list_blocks) + 1)),
						ft_blocknew())))
			return (EXIT_FAILURE);
		ft_hashadd_back(&(term->list_blocks), hash);
		term->ndx_line++;
		term->cursor_pos = PROMPT_SIZE;
		ft_printf("\n> ");
		term->current_block = hash;
		term->ndx_cursor = 0;
		return (PROCESS_SUCCESS);
	}
	return (EXIT_SUCCESS);
}

/*
 ** Manage toutes les touches tape
 ** Return [int] Status de reussite
*/

static int	check_key(t_block *block)
{
	t_term	*term;

	term = *(getterm());
	if (term->last_char == '\033' || term->esc_flag != 0)
		return (escape_sequences(term, block));
	if (term->last_char == DELCHAR || term->last_char == BACKSPACE)
		return (!backspace(term, block));
	if (term->last_char != '\n')
	{
		if (term->last_char == '\t')
		{
			if (ft_tabulation(term, block))
				return (EXIT_FAILURE);
		}
		else
		{
			if (insert(block))
				return (EXIT_FAILURE);
		}
		return (PROCESS_SUCCESS);
	}
	else if (term->last_char == '\n')
		return (ft_return_line(term, block));
	return (EXIT_FAILURE);
}

/*
 ** Manage le key control
 ** Return [int] Status de reussite
 ** TODO En prod, supprimer les debug
*/

int			handle_key(void)
{
	t_term	*term;
	t_block *block;
	int		ret;

	term = (*getterm());
	term->nb_cols = tigetnum(T_COLUMN);
	block = (t_block *)(term->current_block)->value;
	debug(term);
	ret = check_key(block);
	debug(term);
	if (ret == PROCESS_SUCCESS)
		return (PROCESS_SUCCESS);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	term->ndx_line = term->original_line + (block->nb_blocks);
	if (term->ndx_line > term->nb_lines - 1)
	{
		term->ndx_line = term->nb_lines - 1;
		term->original_line = term->ndx_line - (block->nb_blocks - 1);
	}
	(term->last_char == '\n') ? ft_printf("\n") : 0;
	term->ndx_cursor = 0;
	term->cursor_pos = 0;
	return (EXIT_SUCCESS);
}
