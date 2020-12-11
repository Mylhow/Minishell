/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:23:46 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/11 15:26:18 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environement.h"

/*
**  CONCAT_VAR
**  Concatenates name and var args into a string the form of : "name=value"
*/

char	*concat_var(char *name, char *value)
{
	char	*concat;
	char	*concat_buf;

	concat_buf = ft_strjoin(name, "=");
	concat = ft_strjoin(concat_buf, value);
	wrfree(concat_buf);
	return (concat);
}

/*
**  DECONCAT_VAR
**  Deconcatenates from key value pattern "name=value" to a string array with
**	str[0]=name and str[1]=value
**  (this functions does not take care of whitespaces of ifs characters)
*/

char	**deconcat_var(char *var_line)
{
	char	**deconcat;
	char	*equal_sym;

	if (!(equal_sym = ft_strchr(var_line, '=')))
		return (NULL);
	if (!(deconcat = wrmalloc(sizeof(char *) * 3)))
		return (NULL);
	deconcat[2] = NULL;
	deconcat[0] = ft_strndup(var_line, (int)(equal_sym - var_line));
	deconcat[1] = ft_strndup(equal_sym + 1,
		ft_strlen(var_line) - (int)(equal_sym - var_line + 1));
	return (deconcat);
}

int		is_valid_var_name(char *var, size_t sz)
{
	int	i;
	int	eq_sym;

	eq_sym = 0;
	i = 0;
	while (var[i] && i < (int)sz)
	{
		if (!is_valid_bash_char(var[i]))
			return (i != 0 ? 0 : 1);
		i++;
	}
	return ((sz == 0) ? 1 : 0);
}

int		ft_strlchr(char *str, char c)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}
