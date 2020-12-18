/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blocks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:13 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:14 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
 ** Cree un block en se basant sur une chaine de caractère
 ** Return [t_block] Pointeur sur le block nouvellement crée
*/

t_block	*ft_blockstrnew(char *s)
{
	t_block	*ptr;
	t_term	*term;

	term = (*getterm());
	if (!s)
		return (0);
	if (!(ptr = wrmalloc(sizeof(t_block))))
		return (0);
	if (!(ptr->str_cmd = ft_strdup(s)))
		return (0);
	ptr->size = ft_strlen(ptr->str_cmd);
	ptr->nb_blocks = ptr->size / term->nb_cols + 1;
	ptr->alloc_size = term->nb_cols * ptr->nb_blocks + 1 - PROMPT_SIZE;
	return (ptr);
}

/*
 ** Cree une chaine de caractere avec tout les blocks
 **	Return [*t_block] Pointeur de la chaine ou NULL
*/

char	*ft_strjoinblock(t_hash *hash)
{
	t_block	*block;
	char	*str;

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

/*
 ** Duplique l'ensemble des blocs en un seul.
 **	Return [*t_block] Pointeur du nouveau bloc ou NULL
*/

t_block	*ft_blockhashdup(t_hash *hash)
{
	t_block *ptr;
	t_block	*block;

	if (!(ptr = ft_blocknew()))
		return (NULL);
	ptr->alloc_size = 0;
	while (hash)
	{
		block = (t_block *)hash->value;
		if (!(ptr->str_cmd = ft_strjoin(ptr->str_cmd, block->str_cmd)))
			return (NULL);
		ptr->size += block->size;
		ptr->alloc_size += block->alloc_size;
		ptr->nb_blocks = 1;
		hash = hash->next;
	}
	return (ptr);
}
