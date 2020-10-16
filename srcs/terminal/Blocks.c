#include "libft_hash.h"
#include "terminal.h"
#include "libft_printf.h"
#include "libft_mem.h"
#include "libft_string.h"

t_block *ft_blocknew(void)
{
	t_block *ptr;

	if (!(ptr = wrmalloc(sizeof(t_block))))
		return (0);
	ptr->nb_blocks = 1;
	ptr->size = 0;
	if ((ptr->str_cmd = (char *)wrmalloc(STR_SIZE * ptr->nb_blocks)) == 0)
		return (0);
	if ((ptr->str_put = (char *)wrmalloc(STR_SIZE * ptr->nb_blocks)) == 0)
		return (0);
	ft_bzero(ptr->str_cmd, STR_SIZE);
	ft_bzero(ptr->str_put, STR_SIZE);
	ptr->print = ft_blockprint;
	return (ptr);
}

void ft_blockprint(t_block *block)
{
	if (!block)
		return;
	ft_printf("{nbBlocks: %d} = ([%d] '%s') = ('%s')\n", block->nb_blocks, block->size, block->str_cmd, block->str_put);
}