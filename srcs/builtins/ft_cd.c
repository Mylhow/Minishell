/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:46:26 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 10:27:40 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "builtins.h"
#include "libft_printf.h"
#include "expander.h"

static void	exit_malloc(void)
{
	ft_printf("error malloc\n");
	exit(1);
}

static int	return_result(char *origin_fct, char *path,
								int cpy_errno, char **str)
{
	if (cpy_errno)
	{
		ft_printf("minishell: %s: %s\n", origin_fct, strerror(cpy_errno));
		g_exit_status = 1;
		return (1);
	}
	*str = path;
	return (0);
}

int			ft_get_pwd(char *origin_fct, char **str)
{
	int		cpy_errno;
	size_t	len_path;
	char	*path;

	cpy_errno = 34;
	len_path = 5;
	if (!(path = wrmalloc(sizeof(char) * len_path)))
		exit_malloc();
	while (cpy_errno == ERANGE)
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
	return (return_result(origin_fct, path, cpy_errno, str));
}

int			ft_cd(int ac, char **av, char **env)
{
	char	*path;
	int		cpy_errno;

	(void)env;
	path = (ac == 1) ? get_env("HOME") : av[1];
	if (!path || !path[0])
		return (0);
	if (ac > 2)
	{
		ft_printf("minishell: %s: too many arguments\n", av[0]);
		return (1);
	}
	if (chdir(path) == -1)
	{
		cpy_errno = errno;
		ft_printf("minishell: %s: %s: %s\n", av[0], av[1], strerror(cpy_errno));
		g_exit_status = 1;
		return (g_exit_status);
	}
	if (ft_get_pwd(av[0], &path))
		return (1);
	set_var("OLDPWD", get_env("PWD"));
	set_var("PWD", path);
	wrfree(path);
	return (0);
}
