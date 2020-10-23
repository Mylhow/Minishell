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
	ptr->delta_end_line = 0;
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

char		*ft_retcontent(t_hash *hash)
{
	char	*ptr;
	t_block	*block;

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
