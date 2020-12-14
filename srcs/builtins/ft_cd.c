/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:46:26 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/14 08:48:47 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "builtins.h"

//!changer printf par ft_printf
#include <stdio.h>
//#include "libft_printf.h"
//TODO change pwd with the env fcts of Lucas

int		ft_cd(int ac, char **av, char **env)
{
	char	*path;
	int		cpy_errno;

	(void)env;
	path = (ac == 1) ? get_env("HOME") : av[1];
	if (!path || !path[0])
		return (0);
	if (chdir(path) == -1)
	{
		cpy_errno = errno;
		printf("minishell: %s: %s: %s\n", av[0], av[1], strerror(cpy_errno));
		return (1);
	}
	set_var("PWD", path);
	return (0);
}