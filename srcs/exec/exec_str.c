/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:50:26 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/12 13:10:22 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**	Concatenates a location with some file
*/

static char		*path_cat(char *location, char *file)
{
	const size_t	len = ft_strlen(location) + ft_strlen(file) + 2;
	char			*cat;
	char			*c;

	if (!(cat = malloc(len * sizeof(char))))
		return (NULL);
	c = cat;
	while (*location)
		*c++ = *location++;
	*c++ = '/';
	while (*file)
		*c++ = *file++;
	*c++ = 0;
	return (cat);
}

/*
**	Checks if file exists and returns its abolute path on file_path
*/

static bool		get_location(char *file, char **file_path)
{
	char		**locations;
	char		*cat_tmp;

	if (file_exists(file))
	{
		*file_path	= file;
		return (true);
	}
	locations = ft_split(getenv("PATH"), ':');
	while (locations && *locations)
	{
		if (file_exists((cat_tmp = path_cat(*locations, file))))
		{
			free(file);
			*file_path = cat_tmp;
			return (true);
		}
		free(cat_tmp);
		locations++;
	}
	return (false);
}

/*
**	Executes a simple command by string
*/

int				exec_str(char **argv, t_list *redir, char **envp)
{
	pid_t	pid;
	int		status;

	if (redir && (handle_redirection(redir)) == NO_FILE)
		return (NO_FILE);
	if (argv && argv[0] && is_builtin(argv[0]))
	{
		//	TODO builtin support (need to implement execbi(typedef int t_builtin builtin, char **argv, char **envp) )
		printf("Builtin support not implemented yet.\n");
	}
	else if (argv && argv[0] && get_location(argv[0], &argv[0]))
	{
		if ((pid = fork()) == -1)
			return (-1);
		if (pid == 0)
			execve(argv[0], argv, envp);
		status = -1;
		if (waitpid(pid, &status, 0) == -1)
			return (-1);
	}
	else
		printf("%s : command not found\n", argv[0]);
	return (0);
}
