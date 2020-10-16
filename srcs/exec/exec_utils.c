/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:11:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/10/16 15:29:48 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

bool	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (true);
	if (ft_strcmp(str, "cd") == 0)
		return (true);
	if (ft_strcmp(str, "pwd") == 0)
		return (true);
	if (ft_strcmp(str, "export") == 0)
		return (true);
	if (ft_strcmp(str, "unset") == 0)
		return (true);
	if (ft_strcmp(str, "env") == 0)
		return (true);
	if (ft_strcmp(str, "exit") == 0)
		return (true);
	return (false);
}

bool	file_exists(char *file)
{
	struct stat	s;

	if (stat(file, &s) != -1)
		return (true);
	return (false);
}
