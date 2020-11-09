/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:23:45 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/09 18:41:19 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
**  IS_VALID_BASH_CHAR
**  Checks if char c is a valid variable name character, it
**  follows the rule :
**  [0-9][a-z][A-Z][_]
*/

static int		is_valid_bash_char(char c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') ||
		(c >= 'A' && c <= 'Z') || c == '_');
}

/*
**	GET_VAR_NAME
**
**	Description: gets next valid bash variable name
**	in unparsed_var. you need to make it point on
**  the '$' character (example: "$HOME" not "HOME")
**
**	Returns: the name of the next valid bash variable
**  name.
*/

#define VAR_VALID 1
#define VAR_NONE  0

static char		*get_var_name(char *unparsed_var)
{
	size_t	var_len;
	char	*start_var;
	char	*var_name;

	if (!unparsed_var || *unparsed_var != '$')
		return (NULL);
	unparsed_var++;
	start_var = unparsed_var;
	while (is_valid_bash_char(*unparsed_var))
		unparsed_var++;
	var_len = unparsed_var - start_var;
	return (ft_strndup(start_var, var_len));
}

/*
**  PARSE_VAR
**  Parses a bash variable.
**
**  Description: copy unparsed_var environement value in dst,
**  unparsed_var need to start with '$' (ex: "$PATH" is valid
**  but "PATH" is invalid, "$PATHanother_string" is also valid)
**
**  Returns: VAR_VALID if unparsed_var was found, VAR_NONE
**  if unparsed var wasn't found or if unparsed_var didn't
**  start width '$' (return value is allocated)
*/

static int		parse_var(char **dst, char *unparsed_var)
{
	size_t		var_len;
	char		*start_var;
	char		*var_name;

	if (!(var_name = get_var_name(unparsed_var)))
	{
		*dst = NULL;
		return (VAR_NONE);
	}
	// TODO REPLACE getenv by our own implementation of it !
	if (!(*dst = getenv(var_name)))
		return (VAR_NONE);
	return (VAR_VALID);
}

/*
**  Expands environement variables from str in dst
**  (following bash Quoting rules)
*/

int				expand_var(char **dst, const char *str)
{
	int			i;
	char		quotes;
	char		*var_buffer;
	char		*dst_buffer;
	size_t		var_len;

	*dst = ft_strdup(str);
	i = 0;
	while ((*dst)[i])
	{
		if ((*dst)[i] == '$' && is_valid_bash_char((*dst)[i + 1])
		&& quotes != QUOTE_SINGLE)
		{
			parse_var(&var_buffer, *dst + i);
			var_len = ft_strlen(get_var_name(*dst + i));
			if (!var_buffer)
				var_buffer = "";
			dst_buffer = *dst;
			*dst = replace_section(*dst, i, var_buffer, var_len + 1);
			free(dst_buffer);
		}
		quotes = get_quotes(*dst + i);
		i++;
	}
	return (0);
}

