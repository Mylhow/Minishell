/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 12:50:26 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 09:49:45 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "signal_manager.h"
int	g_exit_status = 0;

/*
**	Concatenates a location with some file
*/

static char		*path_cat(char *location, char *file)
{
	const size_t	len = ft_strlen(location) + ft_strlen(file) + 2;
	char			*cat;
	char			*c;

	if (!(cat = wrmalloc(len * sizeof(char))))
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

	if (!*file || !ft_strcmp(file, ".."))
		return (false);
	if (file_exists(file))
	{
		*file_path	= file;
		return (1);
	}
	locations = ft_split(get_env("PATH"), ':');
	while (locations && *locations)
	{
		if (file_exists((cat_tmp = path_cat(*locations, file))))
		{
			wrfree(file);
			*file_path = cat_tmp;
			return (1);
		}
		wrfree(cat_tmp);
		locations++;
	}
	return (0);
}

/*
**	EXEC_PROCESS
**	Executes a process builtin or by location using default arguments
*/
int				exec_process(char **argv)
{
	pid_t	pid;
	int		status;

	if (argv && argv[0] && is_builtin(argv[0]))
		g_exit_status = execbi(argv[0], argv);
	else if (argv && argv[0] && get_location(argv[0], &argv[0]))
	{
		if (!ft_strcmp(argv[0], "."))
		{
			ft_fprintf(STDERR_FILENO, "minishell: .: filename argument required.\n");
			g_exit_status = 2;
			return (2);
		}
		if (check_permissions(argv[0]) != 0 || !is_executable(argv[0]))
			return (1);
		if ((pid = fork()) == -1)
			return (-1);
		if (pid == 0)
			execve(argv[0], argv, g_envp);
		if (waitpid(pid, &status, 0) == -1)
			return (-1);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);	
		else if (WIFSIGNALED(status))
			g_exit_status = WTERMSIG(status) + 128;
		else if (WIFSTOPPED(status))
			g_exit_status = WSTOPSIG(status) + 128;
	}
	else
	{
		if (argv[0][0] == '/' || argv[0][1] == '/' || (argv[0][0] == '.' && argv[0][1] == '/'))
			ft_fprintf(STDERR_FILENO, "minishell: %s: No such file or directory.\n", argv[0]);
		else
			ft_fprintf(2, "minishell: %s: command not found\n", argv[0]);
		g_exit_status = 127;
	}
	wrfree(argv[0]);
	wrfree(argv);
	argv = NULL;
	return (0);
}


/*
**	Executes a simple command by string
*/

int				exec_str(char *str)
{
	t_cmd	*cmd;
	char	**argv;

	argv = NULL;
	cmd = NULL;
	g_interrupt = 0;
	backup_io();
	if (expand_cmd(&cmd, str) != 0)
	{
		wrfree(cmd);
		return (1);
	}
    if (parse_redirections(cmd) != 0)
		return (1);
	if (parse_argv(&argv, cmd->l_argv) != 0)
		return (1);
	fflush(stdout);
	if (cmd->l_redir && (handle_redirection(cmd->l_redir)) != 0)
		return (1);
	if (exec_process(argv) != 0)
		return (1);
	wrfree(cmd);
	restore_io();
	return (0);
}
