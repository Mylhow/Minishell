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
	ptr->size = 0;
	ptr->alloc_size = term->nb_cols + 1 - PROMPT_SIZE;
	if ((ptr->str_cmd = (char *)wrmalloc(ptr->alloc_size)) == 0)
		return (0);
	if ((ptr->str_put = (char *)wrmalloc(ptr->alloc_size)) == 0)
		return (0);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	ft_bzero(ptr->str_put, ptr->alloc_size);
	ptr->print = ft_blockprint;
	return (ptr);
}

void ft_blockprint(t_block *block)
{
	if (!block)
		return;
	ft_printf("{nbBlocks: %d} = ([%d] '%s') = ('%s')\n", block->nb_blocks, block->size, block->str_cmd, block->str_put);
}