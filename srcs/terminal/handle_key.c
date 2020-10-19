#include "terminal.h"
#include <stdio.h>
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_number.h"
#include "libft_printf.h"

static void	insert(t_block *block)
{
    t_term	*term;
    char	*tmp;

    term = (*getTerm());
	put_cursor(term->cursor_pos, term->ndx_line);
	if (term->ndx_cursor < block->size)
	{
		tmp = ft_strdup(block->str_cmd);
		ft_bzero(block->str_cmd, block->size);
		ft_memcpy(block->str_cmd, tmp, term->ndx_cursor);
		block->str_cmd[term->ndx_cursor] = term->last_char;
		ft_strcat(block->str_cmd, tmp + term->ndx_cursor);
		put_caps(T_CLEOL, 0);
		ft_printf("%s", block->str_cmd + term->ndx_cursor );
	}
	else
	{
		block->str_cmd[block->size] = term->last_char;
		ft_printf("%s", block->str_cmd + block->size);
	}
	term->ndx_cursor++;
	term->cursor_pos++;
    block->size++;
	put_cursor(term->cursor_pos, term->ndx_line);
}

static int ft_return_line(t_term *term, t_block *block)
{
	t_hash	*hash;

	if (block->str_cmd[block->size - 1] == '\\')
	{
		if (!(hash = ft_hashnew(ft_strjoin("block_",
										    ft_itoa(ft_hashlen(term->list_blocks) + 1)), ft_blocknew())))
			return (EXIT_FAILURE);
		ft_hashadd_back(&(term->list_blocks), hash);
		term->ndx_line++;
		term->cursor_pos = PROMPT_SIZE;
		printf("\n> ");
		term->current_block = hash;
		term->ndx_cursor = 0;
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	check_key(t_block *block)
{
    t_term  *term;

    term = *(getTerm());
    if (term->last_char == '\033' || term->esc_flag != 0)
        return (escape_sequences(block));
    if (term->last_char == DELCHAR || term->last_char == BACKSPACE)
        return (!backspace(block));
    if (term->last_char != '\n')
    {
		if (block->size == block->alloc_size - 1)
        {
			block->nb_blocks++;
			block->alloc_size += term->nb_cols;
			if (!(block->str_cmd = realloc_str(block->str_cmd, block->alloc_size)))
				return (EXIT_FAILURE);
			// term->ndx_line +=1;
        }
        insert(block);
		if (term->cursor_pos == term->nb_cols)
		{
			ft_printf("\n");
			term->cursor_pos = 0;
			term->ndx_line++;
			if (term->ndx_line > term->nb_lines - 1)
				term->ndx_line = term->nb_lines - 1;
		}
		return (2);
    }
    else
		return (ft_return_line(term, block));
}

//TODO gerer fleche de droite pour multi-lignes
//TODO gerer le nombre max de lignes
int			handle_key()
{
    t_term	*term;
    t_block *block;
	int 	ret;

    term = (*getTerm());
    // debug(term);
	term->nb_cols = tigetnum(T_COLUMN);
	block = (t_block *)(term->current_block)->value;
	ret = check_key(block);
	// debug(term);
	if (ret == 2)
		return (2);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
	term->ndx_line += (block->size - term->ndx_cursor) / term->nb_cols + 1;
	if (term->ndx_line > term->nb_lines - 1)
		term->ndx_line = term->nb_lines - 1;
    if (block->str_cmd[0] == '\0' || term->last_char == '\n')
        ft_printf("\n");
    term->ndx_cursor = 0;
	term->cursor_pos = 0;
    block->size = 0;
	block->delta_end_line = 0;
	// debug(term);
	return (EXIT_SUCCESS);
}
