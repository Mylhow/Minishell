#include "libft_hash.h"
#include "terminal.h"
#include "libft_printf.h"
#include "libft_mem.h"
#include "libft_string.h"

t_block *ft_blocknew(void)
{
	t_block *ptr;
	t_term *term;

	term = (*getTerm());
	if (!(ptr = wrmalloc(sizeof(t_block))))
		return (0);
	ptr->nb_blocks = 1;
	ptr->delta_end_line = 0;
	ptr->size = 0;
	ptr->alloc_size = term->nb_cols + 1 - PROMPT_SIZE;
	if ((ptr->str_cmd = (char *)wrmalloc(ptr->alloc_size)) == 0)
		return (0);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	ptr->print = ft_blockprint;
	return (ptr);
}

void ft_blockprint(t_block *block)
{
	if (!block)
		return;
	ft_printf("{nbBlocks: %d} = ([%d] '%s')\n", block->nb_blocks, block->size, block->str_cmd);
}

char *ft_retcontent(t_hash *hash)
{
	char *ptr;
	t_block *block;

	ptr = 0;
	while (hash)
	{
		block = (t_block *)hash->value;
		if (!(ptr = ft_strjoin(ptr, block->str_cmd)))
			return (0);
		hash = hash->next;
	}
	return (ptr);
}