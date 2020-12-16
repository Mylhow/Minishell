/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:29:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 15:30:22 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

/*
**	Backup variables used to store stdin/stdout original fds
*/
static int	g_stdin_backup = 0;
static int	g_stdout_backup = 1;

/*
**	BACKUP_IO
**	Backups the stdin/stdout
**	0 = stdin
**	1 = stdout
**	2 = stdin + stdout
*/

int		backup_io(int mode)
{
	if (mode == 0 || mode == 2)
		g_stdin_backup = dup(STDIN_FILENO);
	if (mode == 1 || mode == 2)
		g_stdout_backup = dup(STDOUT_FILENO);
	return (0);
}

/*
**	RESTORE_IO
**	Restore the stdin/stdout based on previously backuped ones using backup_io()
**	0 = stdin
**	1 = stdout
**	2 = stdin + stdout
*/

int		restore_io(int mode)
{
	if (mode == 0 || mode == 2)
	{
		dup2(g_stdin_backup, STDIN_FILENO);
		close(g_stdin_backup);
	}
	if (mode == 1 || mode == 2)
	{
		dup2(g_stdout_backup, STDOUT_FILENO);
		close(g_stdout_backup);
	}
	backup_io(mode);
	return (0);
}

/*
**	REDIRECT_STDOUT
**	Opens file and redirects stdout into its fd.
*/

int		redirect_stdout(char *file)
{
	int		fd;

	restore_io(M_STDOUT);
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, DEFAULT_PERM)) <= 0)
	{
		restore_io(M_FULLIO);
		g_exit_status = 1;
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s.\n",
		file, strerror(errno));
		return (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

/*
**	APPEND_STDOUT
**	Opens file with flag O_APPEND and redirects stdout into its fd with.
*/

int		append_stdout(char *file)
{
	int		fd;

	restore_io(M_STDOUT);
	if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, DEFAULT_PERM)) <= 0)
	{
		restore_io(M_FULLIO);
		g_exit_status = 1;
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s.\n",
		file, strerror(errno));
		return (EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

/*
**	REDIRECT_STDIN
**	Opens file and redirects stdin into its fd.
*/

int		redirect_stdin(char *file)
{
	int		fd;

	restore_io(M_STDIN);
	if ((fd = open(file, O_RDONLY, DEFAULT_PERM)) <= 0)
	{
		restore_io(M_FULLIO);
		g_exit_status = 1;
		ft_fprintf(STDERR_FILENO, "minishell: %s: %s.\n",
		file, strerror(errno));
		return (NO_FILE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}
