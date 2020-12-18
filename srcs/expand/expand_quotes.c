/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 11:17:33 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/18 16:07:24 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static size_t	get_trimmed_quotes_len(char *str)
{
	char		quotes;
	int			i;
	size_t		out_len;

	out_len = ft_strlen(str);
	i = 0;
	quotes = get_quotes(QUOTE_RESET);
	while (str[i])
	{
		if (quotes != QUOTE_SINGLE && str[i] == '\\')
		{
			out_len--;
			i++;
		}
		else if ((quotes == QUOTE_NONE && (str[i] == QUOTE_SINGLE
		|| str[i] == QUOTE_DOUBLE))
		|| (quotes != QUOTE_NONE && str[i] == quotes))
			out_len--;
		quotes = get_quotes(str + i);
		i++;
	}
	return (out_len);
}

static int		expand_quotes_str(char **dst, char *str)
{
	size_t		out_len;
	int			i;
	int			j;
	char		quotes;

	quotes = get_quotes(QUOTE_RESET);
	out_len = get_trimmed_quotes_len(str);
	if (!(*dst = wrmalloc(sizeof(char) * (out_len + 1))))
		return (1);
	i = 0;
	j = 0;
	while (i < (int)out_len && str[j])
	{
		quotes = get_quotes(str + j);
		if (quotes != QUOTE_SINGLE && str[j] == '\\')
			(*dst)[i++] = str[++j];
		else if (!(quotes == QUOTE_NONE && (str[j] == QUOTE_SINGLE
		|| str[j] == QUOTE_DOUBLE))
		&& (str[j] != quotes))
			(*dst)[i++] = str[j];
		j++;
	}
	(*dst)[out_len] = '\0';
	return (0);
}

/*
**	EXPAND_QUOTES
**	Performs the quote removal shell expansion
*/

int				expand_quotes(t_cmd *src)
{
	t_list	*argv;
	char	*buff;

	argv = src->l_argv;
	while (argv)
	{
		buff = argv->content;
		expand_quotes_str((char **)&argv->content, (char *)argv->content);
		wrfree(buff);
		argv = argv->next;
	}
	return (0);
}
