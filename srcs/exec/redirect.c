/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 14:29:15 by lrobino           #+#    #+#             */
/*   Updated: 2020/10/16 17:38:26 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int		redirect_stdout(char *file)
{
	int		fd;

	if ((fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, DEFAULT_PERM)) <= 0)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int		append_stdout(char *file)
{
	int		fd;

	if ((fd = open(file, O_WRONLY | O_CREAT | O_APPEND, DEFAULT_PERM)) <= 0)
		return (-1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}

int		redirect_stdin(char *file)
{
	int		fd;

	if ((fd = open(file, O_RDONLY, DEFAULT_PERM)) <= 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return (NO_FILE);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (EXIT_SUCCESS);
}
