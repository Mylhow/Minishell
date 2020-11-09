/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 15:33:47 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/09 15:58:40 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char		*replace_section
	(char *str, int index, const char *replace, size_t pattern_len)
{
	int		j;
	size_t	out_len;
	size_t	replace_len;
	char	*out;

	replace_len = ft_strlen(replace);
	out_len = ft_strlen(str) - pattern_len + replace_len;
	if (!(out = (char *)malloc(sizeof(char) * (out_len + 1))))
		return (NULL);
	j = -1;
	while (++j < index)
		out[j] = str[j];
	while ((j - index) < replace_len)
	{
		out[j] = replace[j - index];
		j++;
	}
	while (str[index + pattern_len])
		out[j++] = str[index++ + pattern_len];
	out[out_len] = '\0';
	return (out);
}

char		*ft_strreplace
	(const char *s, const char *pattern, const char *replace)
{
	int		i;
	int		j;
	size_t	pattern_len;
	char	*str;
	char	*strbuff;

	i = 0;
	pattern_len = ft_strlen(pattern);
	strbuff = ft_strdup(s);
	while (strbuff[i])
	{
		j = 0;
		while (strbuff[i + j] && pattern[j] && strbuff[i + j] == pattern[j])
			j++;
		if (j == pattern_len)
		{
			str = replace_section(strbuff, i, replace, pattern_len);
			free(strbuff);
			strbuff = str;
			i = 0;
			continue;
		}
		i++;
	}
	return ((char *)strbuff);
}

char		*ft_strlreplace
	(const char *s, const char *pattern, const char *replace, size_t n)
{
	int		i;
	int		j;
	size_t	pattern_len;
	char	*str;
	char	*strbuff;

	i = 0;
	pattern_len = ft_strlen(pattern);
	strbuff = ft_strdup(s);
	while (i < n)
	{
		j = 0;
		while (strbuff[i + j] && pattern[j] && strbuff[i + j] == pattern[j])
			j++;
		if (j == pattern_len)
		{
			str = replace_section(strbuff, i, replace, pattern_len);
			free(strbuff);
			strbuff = str;
			i = 0;
			continue;
		}
		i++;
	}
	return ((char *)strbuff);
}
