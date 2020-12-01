#include "terminal.h"
#include "libft_mem.h"
#include "libft_string.h"

/*
 ** Créer et initialisation d'un nouveau bloc
 ** Return [*t_block] Pointeur du nouveau bloc ou NULL
*/

t_block	*ft_blocknew(void)
{
	t_block	*ptr;
	t_term	*term;

	term = (*getterm());
	if (!(ptr = wrmalloc(sizeof(t_block))))
		return (NULL);
	ptr->nb_blocks = 1;
	ptr->size = 0;
	ptr->alloc_size = term->nb_cols + 1 - PROMPT_SIZE;
	if ((ptr->str_cmd = (char *)wrmalloc(ptr->alloc_size)) == 0)
		return (NULL);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	return (ptr);
}

/*
 ** Duplique l'ensemble des blocs en un seul.
 **	Return [*t_block] Pointeur du nouveau bloc ou NULL
*/

char	*ft_strjoinblock(t_hash *hash)
{
	t_block	*block;
	char 	*str;

	str = 0;
	while (hash)
	{
		block = (t_block *)hash->value;
		if (!(str = ft_strjoin(str, block->str_cmd)))
			return (NULL);
		hash = hash->next;
	}
	return (str);
}

/*
 ** Duplique un bloc
 ** Return [*t_block] Pointeur sur le bloc ou NULL
*/

t_block	*ft_blockdup(t_block *block)
{
	t_block *ptr;
	int		i;

	i = -1;
	if (!block || !(ptr = ft_blocknew()))
		return (NULL);
	ptr->size = block->size;
	ptr->alloc_size = block->alloc_size;
	ptr->nb_blocks = block->nb_blocks;
	if (!(ptr->str_cmd = wrmalloc(block->alloc_size)))
		return (NULL);
	ft_bzero(ptr->str_cmd, ptr->alloc_size);
	while (block->str_cmd[++i])
	{
		ptr->str_cmd[i] = block->str_cmd[i];
	}
	return (ptr);
}
