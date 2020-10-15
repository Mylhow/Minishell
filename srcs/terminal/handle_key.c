#include "terminal.h"
#include <stdio.h>
#include "libft_mem.h"
#include "libft_string.h"
#include "libft_number.h"
#include "libft_printf.h"


static void	insert(t_block *block)
{
    t_term *term;
    int i;

    i = 0;
    term = (*getTerm());
    block->str_cmd[block->ndx_str] = term->last_char;
    put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
    ft_printf("%s", block->str_cmd + block->ndx_str);
    term->ndx_cursor++;
    block->ndx_str++;
    block->size++;
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
		term->ndx_cursor = 0;
		printf("\n> ");
		term->current_block = hash;
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	check_key(t_block *block)
{
    t_term  *term;

    term = (*getTerm());
    if (term->last_char == '\033' || term->esc_flag == 1 || term->esc_flag == 2)
        return (escape_sequences(block));
    if (term->last_char == 127 || term->last_char == 8)
        return (!backspace(block));
    if (term->last_char != '\n')
    {
		if (block->ndx_str == STR_SIZE * block->nb_blocks)
        {
			block->nb_blocks++;
			if (!(block->str_cmd = realloc_str(block->str_cmd, (block->nb_blocks) * STR_SIZE)))
				return (EXIT_FAILURE);
        }
        insert(block);
		debug(term);
		return (2);
    }
    else
		return (ft_return_line(term, block));
}

int			handle_key()
{
    t_term	*term;
    t_block *block;
	int 	ret;

    term = (*getTerm());
    debug(term);
	block = (t_block *)(term->current_block)->value;
	ret = check_key(block);
	if (ret == 2)
		return (2);
	if (ret == EXIT_FAILURE)
		return (EXIT_FAILURE);
    if (block->str_cmd[0] == '\0' || term->last_char == '\n')
        ft_printf("\n");
    term->ndx_cursor = 0;
    block->ndx_str = 0;
    block->size = 0;
    term->ndx_line++;
	debug(term);
	return (EXIT_SUCCESS);
}
