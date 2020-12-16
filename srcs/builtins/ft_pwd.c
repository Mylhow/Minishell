/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:21:45 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/16 12:38:11 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "builtins.h"

static void	exit_malloc(void)
{
	ft_printf("error malloc\n");
	exit(1);
}

static int	return_result(char **av, char *path, int cpy_errno)
{
	if (cpy_errno)
	{
		ft_printf("minishell: %s: %s\n", av[0], strerror(cpy_errno));
		return (1);
	}
	ft_printf("%s\n", path);
	wrfree(path);
	return (0);
}

int			ft_pwd(int ac, char **av, char **env)
{
	int		cpy_errno;
	size_t	len_path;
	char	*path;

	(void)ac;
	(void)env;
	cpy_errno = 34;
	len_path = 5;
	if (!(path = wrmalloc(sizeof(char) * len_path)))
		exit_malloc();
	while (cpy_errno == 34)
	{
		wrfree(path);
		len_path = len_path * 2;
		if (!(path = wrmalloc(sizeof(char) * len_path)))
			exit_malloc();
		if (getcwd(path, len_path))
		{
			cpy_errno = 0;
			break ;
		}
		cpy_errno = errno;
	}
	return (return_result(av, path, cpy_errno));
}
