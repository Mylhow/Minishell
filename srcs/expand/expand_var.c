/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 17:23:45 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 13:46:05 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/*
**	GET_VAR_NAME
**get_var_name
**	Description: gets next valid bash variable name
**	in unparsed_var. you need to make it point on
**  the '$' character (example: "$HOME" not "HOME")
**
**	Returns: the name of the next valid bash variable
**  name.
*/

static char		*get_var_name(char *unparsed_var)
{
	size_t	var_len;
	char	*start_var;

	if (unparsed_var[1] == '?')
		return ("?");
	if (!unparsed_var || *unparsed_var != '$')
		return (NULL);
	unparsed_var++;
	start_var = unparsed_var;
	if (!ft_isalpha(*unparsed_var))
		return (NULL);
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
	char		*var_name;

	if (unparsed_var[1] == '?')
	{
		*dst = ft_itoa(g_exit_status % 255);
		return (VAR_VALID);
	}
	if (!(var_name = get_var_name(unparsed_var)))
	{
		*dst = NULL;
		return (VAR_NONE);
	}
	if (!(*dst = get_env(var_name)) || *dst[0] == '\0')
	{
		*dst = NULL;
		return (VAR_NONE);
	}
	return (VAR_VALID);
}

/*
**	CHECK_AMBIGUOUS
**
**	Checks for a variable if its preceded by a redirection character,
**	this function should be call only for vaiable that are determined null.
**	It will return VAR_AMBIGUOUS if preceded by redirection or VAR_VALID if
**	it is not.
*/

static int		check_ambiguous(char *var, char *var_buffer, int index)
{
	int		i;

	i = index;
	while (index > 1 && (is_ifs(var[index]) || var[index] == '$'))
		index--;
	if (is_redirect(var + index) &&
		(var_buffer == NULL || contains_ifs(var_buffer)))
	{
		ft_fprintf(STDERR_FILENO, "minishell: $%s: ambiguous redirection\n",
			get_var_name(var + i));
		return (VAR_AMBIGUOUS);
	}
	return (VAR_VALID);
}

static char		*get_var_buff(char **dst, int i, char quotes)
{
	char	*dst_buffer;
	char	*var_buffer;
	size_t	var_len;

	if ((*dst)[i] == '$' && (i == 0 || (i > 0 && (*dst)[i - 1] != '\\')) &&
	(is_valid_bash_char((*dst)[i + 1]) || (*dst)[i + 1] == '?')
	&& quotes != QUOTE_SINGLE)
	{
		parse_var(&var_buffer, *dst + i);
		if (check_ambiguous(*dst, var_buffer, i) == VAR_AMBIGUOUS)
			return ((void *)1);
		var_len = ft_strlen(get_var_name(*dst + i));
		if (!var_buffer)
			var_buffer = "";
		dst_buffer = *dst;
		*dst = replace_section(*dst, i, var_buffer, var_len + 1);
		wrfree(dst_buffer);
		return (var_buffer);
	}
	return (NULL);
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

	quotes = get_quotes(QUOTE_RESET);
	*dst = ft_strdup(str);
	i = 0;
	while ((*dst)[i])
	{
		if ((var_buffer = get_var_buff(dst, i, quotes)) == (void *)1)
			return (-1);
		if (var_buffer && var_buffer[0] == '\0')
			var_buffer = NULL;
		else
		{
			quotes = get_quotes(*dst + i);
			i++;
		}
	}
	return (0);
}
