/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 15:55:21 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 13:46:10 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static t_cmd	*create_cmd(void)
{
	t_cmd	*cmd;

	if (!(cmd = wrmalloc(sizeof(t_cmd))))
		return (NULL);
	cmd->l_argv = NULL;
	cmd->l_redir = NULL;
	return (cmd);
}

static int		create_word(t_cmd **cmd, char *str, int start_point, int i)
{
	if (start_point != i)
	{
		if (!(*cmd)->l_argv)
			(*cmd)->l_argv =
			ft_lstnew(ft_strndup(str + start_point, i - start_point));
		else
			ft_lstadd_back(&((*cmd)->l_argv),
			ft_lstnew(ft_strndup(str + start_point, i - start_point)));
	}
	return (0);
}

static int		append_redirect(t_cmd **cmd, char *str, int *i, int *s_point)
{
	int	r_len;

	create_word(cmd, str, *s_point, *i);
	r_len = is_redirect(str + *i + 1) ? 2 : 1;
	ft_lstadd_back(&((*cmd)->l_argv),
	ft_lstnew(ft_strndup(str + *i, is_redirect(str + *i + 1) ? 2 : 1)));
	*s_point = *i + r_len;
	*i += r_len - 1;
	return (0);
}

/*
**  EXPAND_WORD
**  Performs word expansion based on simple command str, and puts it in dst.
*/

int				expand_word(t_cmd **cmd, char *str)
{
	int		i;
	int		start_point;
	char	quotes;

	i = -1;
	start_point = 0;
	quotes = get_quotes(QUOTE_RESET);
	if (!(*cmd = create_cmd()))
		return (1);
	while (str[++i])
	{
		quotes = get_quotes(str + i);
		while ((str[i] == '\0' ||
			is_ifs(str[i])) && quotes == QUOTE_NONE && !is_redirect(str + i))
		{
			create_word(cmd, str, start_point, i);
			if (str[i] == '\0' || !(i++ && (start_point = i)))
				return (0);
			quotes = get_quotes(str + i);
		}
		if (is_redirect(str + i) && quotes == QUOTE_NONE)
			append_redirect(cmd, str, &i, &start_point);
	}
	create_word(cmd, str, start_point, i);
	return (0);
}
