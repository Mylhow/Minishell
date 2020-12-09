/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:55:21 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/04 14:51:04 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
#include <stdio.h>

static int	append_word(t_cmd **cmd, char *str, int start_point, int i)
{
	if (start_point != i)
	{
		if (!(*cmd)->l_argv)
			(*cmd)->l_argv = ft_lstnew(ft_strndup(str + start_point, i - start_point));
		else
			ft_lstadd_back(&((*cmd)->l_argv), ft_lstnew(ft_strndup(str + start_point, i - start_point)));
	}
	return (0);
}

/*
**  EXPAND_WORD
**  Performs word expansion based on simple command str, and puts it in dst.
*/
int     	expand_word(t_cmd **cmd, char *str)
{
	int i;
	int start_point;
	int last_redirect;
	char quotes;

	i = 0;
	start_point = 0;
	last_redirect = 0;
	quotes = get_quotes(QUOTE_RESET);
	if (!(*cmd = wrmalloc(sizeof (**cmd))))
		return (1);
	(*cmd)->l_argv = NULL;
	(*cmd)->l_redir = NULL;
	while (str[i])
	{
		while ((str[i] == '\0' || is_ifs(str[i])) && quotes == QUOTE_NONE && !is_redirect(str+i))
		{
			append_word(cmd, str, start_point, i);
			if (str[i] != '\0')
				i++;
			else
				return (0);
			start_point = i;
			quotes = get_quotes(str + i);
		}
		if (is_redirect(str + i) && quotes == QUOTE_NONE && !last_redirect)
		{
			last_redirect = 1;
			append_word(cmd, str, start_point, i);
			int r_len =  is_redirect(str + i + 1) ? 2 : 1;
			ft_lstadd_back(&((*cmd)->l_argv), ft_lstnew(ft_strndup(str + i, is_redirect(str + i + 1) ? 2 : 1)));
			start_point = i + r_len;
			i+=r_len-1;
		}
		if (last_redirect)
			last_redirect = 0;
		i++;
		quotes = get_quotes(str + i);
	}
	append_word(cmd, str, start_point, i);
	return (0);
}
