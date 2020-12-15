/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:11:41 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 11:56:38 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "builtins.h"

exec_builtin	is_builtin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (ft_echo);
	if (ft_strcmp(str, "cd") == 0)
		return (ft_cd);
	if (ft_strcmp(str, "pwd") == 0)
		return (ft_pwd);
	if (ft_strcmp(str, "export") == 0)
		return (ft_export);
	if (ft_strcmp(str, "unset") == 0)
		return (ft_unset);
	if (ft_strcmp(str, "env") == 0)
		return (ft_env);
	if (ft_strcmp(str, "exit") == 0)
		return (ft_exit);
	return (NULL);
}

bool	file_exists(char *file)
{
	struct stat	s;

	if (stat(file, &s) == 0)
		return (true);
	return (false);
}

bool	is_executable(char *file)
{
	struct stat	s;

	if (stat(file, &s) == 0 && s.st_mode & S_IXUSR)
		return (true);
	ft_fprintf(STDERR_FILENO, "minishell: %s: Permission denied.\n", file);
	return (false);
}

int		parse_argv(char ***argv, t_list	*l_argv)
{
	char	*content_buffer;
	int		index;
	int		size;

	size = ft_lstsize(l_argv);
	if (!(*argv = (char **)wrmalloc(sizeof (char **) * (size + 1))))
		return (1);
	(*argv)[size] = NULL;
	index = 0;
	while (l_argv)
	{
		content_buffer = (char *)l_argv->content;
		if (content_buffer && index < size)
		{
			(*argv)[index] = content_buffer;
			index++;
		}
		l_argv = l_argv->next;
	}
	return (0);
}
