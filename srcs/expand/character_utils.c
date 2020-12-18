/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   character_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:45:37 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/18 16:08:26 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	is_redirect(char *c)
{
	if (ft_strncmp(c, ">>", 2) == 0 || ft_strncmp(c, ">", 1) == 0 ||
	ft_strncmp(c, "<", 1) == 0)
		return (1);
	return (0);
}

/*
**	IS_IFS
**	Checks if c is an Input Field Separator character
**	Bash default is: $IFS=" \t\n"
*/

char	is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/*
**	IS_IFS
**	Checks if str is made of IFS characters
**	Bash default is: $IFS=" \t\n"
*/

int		contains_ifs(char *str)
{
	while (str && *str)
	{
		if (is_ifs(*str))
			return (1);
		str++;
	}
	return (0);
}

/*
**  IS_VALID_BASH_CHAR
**  Checks if char c is a valid bash variable name character, it
**  follows the rule :
**  [0-9][a-z][A-Z][_]
*/

int		is_valid_bash_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') || c == '_');
}

int		is_escaped(char *c, int p)
{
	int	count;

	count = 0;
	if (p <= 0)
		return (0);
	while (--p && c[p] == '\\')
		count++;
	return (count % 2);
}
