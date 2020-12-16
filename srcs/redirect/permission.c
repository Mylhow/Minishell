/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permission.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 14:28:21 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 15:05:57 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

int	check_permissions(char *file, int oflag)
{
	struct stat st;

	if (open(file, oflag, DEFAULT_PERM) < 0)
	{
		g_exit_status = 1;
		ft_fprintf(STDERR_FILENO,
		"minishell: %s: %s.\n", file, strerror(errno));
		return (-1);
	}
	if (stat(file, &st) != 0)
		return (-1);
	if (st.st_mode & S_IFDIR)
	{
		g_exit_status = 126;
		ft_fprintf(STDERR_FILENO,
		"minishell: %s: Is a directory.\n", file);
		return (-1);
	}
	return (0);
}

int	is_file(char *file)
{
	struct stat st;

	if (stat(file, &st) != 0)
		return (0);
	return (1);
}
