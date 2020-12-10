/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 13:21:45 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/10 13:46:49 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>

//!changer malloc et free avec le wrapper
//!changer printf avec ft_printf
#include <stdlib.h>
#include <stdio.h>

static void	exit_malloc(void)
{
	printf("error malloc\n");
	exit(1);
}


static int	return_result(char **av, char *path, int cpy_errno)
{
	if (cpy_errno)
	{
		printf("minishell: %s: %s\n", av[0], strerror(cpy_errno));
		return (1);
	}
	printf("%s\n", path);
	return (0);
}

int			ft_pwd(int ac, char **av, char **env)
{
	(void)ac;
	(void)env;
	int		cpy_errno;
	size_t	len_path;
	char	*path;

	cpy_errno = 34;
	len_path = 5;
	if (!(path = malloc(sizeof(char) * len_path)))
		exit_malloc();
	while (cpy_errno == 34)
	{
		free(path);
		len_path = len_path * 2;
		if (!(path = malloc(sizeof(char) * len_path)))
			exit_malloc();
		if (getcwd(path, len_path))
		{
			cpy_errno = 0;
			break;
		}
		cpy_errno = errno;
	}
	return(return_result(av, path, cpy_errno));
}