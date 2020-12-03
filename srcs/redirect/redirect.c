/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:29:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/03 16:54:25 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"

/*
**	Backup variables used to store stdin/stdout original fds
*/
int	g_stdin_backup = 0;
int	g_stdout_backup = 1;

/*
**	BACKUP_IO
**	Backups the stdin/stdout
*/

int		backup_io(void)
{
	g_stdin_backup = dup(STDIN_FILENO);
	g_stdout_backup = dup(STDOUT_FILENO);
	return (0);
}

/*
**	RESTORE_IO
**	Restore the stdin/stdout based on previously backuped ones using backup_io()
*/

int		restore_io(void)
{
	dup2(g_stdin_backup, STDIN_FILENO);
	dup2(g_stdout_backup, STDOUT_FILENO);
	close(g_stdin_backup);
	close(g_stdout_backup);
	backup_io();
	return (0);
}

/*
**	REDIRECT_STDOUT
**	Opens file and redirects stdout into its fd.
*/

int		redirect_stdout(char *file)
{
	int		fd;

	restore_io();
	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, DEFAULT_PERM)) <= 0)
		return (-1);
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

	restore_io();
	if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, DEFAULT_PERM)) <= 0)
		return (-1);
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

	restore_io();
	if ((fd = open(file, O_RDONLY, DEFAULT_PERM)) <= 0)
	{
		ft_printf("minishell: %s: No such file or directory\n", file);
		return (NO_FILE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}
