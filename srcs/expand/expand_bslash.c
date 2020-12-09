/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_bslash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 14:18:16 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/04 14:10:10 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int  expand_bslash_str(char **dst, char *str)
{
    int     i;
    char    *out;
    size_t  out_len;

    i = 0;
    out_len = 0;
    while (str[i])
    {
        if (str[i] == '\\')
        {
            if (i > 0 && str[i - 1] == '\\')
                out_len++;
        }
        else
            out_len++;
        i++;
    }
    if (!(out = malloc(sizeof(char) * out_len + 1)))
        return (0);
    i = 0;
    while (i < (int)out_len)
    { 
        if (*str == '\\')
        {
            if (i == 0 || *(str - 1) != '\\')
                str++;
        }
        out[i++] = *str++;
    }
    out[out_len] = '\0';
    *dst = out;
    return (0);
}

/*
**  EXPAND_BSLASH
**  Performs the backslash shell expansion
*/
int				expand_bslash(t_cmd *src)
{
	t_list	*argv;
	char	*buff;

	argv = src->l_argv;
	while (argv)
	{
		buff = argv->content;
		expand_bslash_str((char **)&argv->content, (char *)argv->content);
		wrfree(buff);
		argv = argv->next;
	}
	return (0);
}