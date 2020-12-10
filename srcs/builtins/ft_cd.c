/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:46:26 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/10 13:43:00 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

//!changer printf par ft_printf
#include <stdio.h>
//#include "libft_printf.h"
//TODO changer getenv par notre fonction
//TODO change pwd with the env fcts of Lucas

int		ft_cd(int ac, char **av, char **env)
{
	char	*path;
	int		cpy_errno;

	path = (ac == 1) ? getenv("HOME") : av[1];
	if (!path || !path[0])
		return (0);
	if (chdir(path) == -1)
	{
		cpy_errno = errno;
		printf("minishell: %s: %s: %s\n", av[0], av[1], strerror(cpy_errno));
		return (1);
	}
	return (0);
}