#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"

/*
 ** Créer et initialisation d'un nouveau bloc
 ** return : pointeur sur le nouveau bloc
*/

t_block		*ft_blocknew(void)
{
	t_block	*ptr;
	t_term	*term;

	term = (*getTerm());
	if (!(ptr = wrmalloc(sizeof(t_block))))
		return (0);
	ptr->nb_blocks = 1;
	ptr->size = 0;
	ptr->alloc_size = term->nb_cols + 1 - PROMPT_SIZE;
	if ((ptr->str_cmd = (char *)wrmalloc(ptr->alloc_size)) == 0)
		return (0);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	return (ptr);
}

/*
 ** Concatène l'ensemble des blocs
 **	return : pointeur de la chaine de caractère
*/
#include "libft_printf.h"
t_block	*ft_blockhashdup(t_hash *hash)
{
	t_block *ptr;
	t_block	*block;

	if (!(ptr = ft_blocknew()))
		return (0);
	ptr->alloc_size = 0;
	while (hash)
	{
		block = (t_block *)hash->value;
		if (!(ptr->str_cmd = ft_strjoin(ptr->str_cmd, block->str_cmd)))
			return (0);
		ptr->size += block->size;
		ptr->alloc_size += block->alloc_size;
		ptr->nb_blocks = 1;
		hash = hash->next;
	}
	return (ptr);
}

t_block *ft_blockdup(t_block *block)
{
	t_block *ptr;
	int 	i;

	i = -1;
	if (!block || !(ptr = ft_blocknew()))
		return (0);
	ptr->size = block->size;
	ptr->alloc_size = block->alloc_size;
	ptr->nb_blocks = block->nb_blocks;
	if (!(ptr->str_cmd = wrmalloc(block->alloc_size)))
		return (0);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	while (block->str_cmd[++i])
	{
		ptr->str_cmd[i] = block->str_cmd[i];
	}
	return (ptr);
}
