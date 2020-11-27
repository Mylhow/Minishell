/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_tool.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 15:45:19 by abourbou          #+#    #+#             */
/*   Updated: 2020/11/27 12:21:47 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "syntax_error.h"

// push the index to the end of the quote
// return 0 if success or return the quote if syntax error
char	pass_quotes(char *str, int *index)
{
	int		i;
	char	quote;

	i = *index;
	quote = str[i];
	i++;
	while(str[i] && str[i] != quote)
		i++;
	if (!str[i])
		return (quote);
	*index = i;
	return (0);
}

void	pass_blank(char *str, int *index)
{
	int i;

	i = *index;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
		i++;
	*index = i;
}

char	print_syntax_err(void)
{
	ft_printf("our bash : syntax error\n");
	return (NEW_COMMAND);
}