/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:30:07 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/16 12:30:25 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_mem.h"
#include "terminal.h"
#include "libft_printf.h"
#include "libft_ctype.h"
#include "libft_number.h"
#include <ncurses.h>

static int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	ft_quit(int number)
{
	if (tcsetattr(1, 0, &(*getterm())->termios_backup) == -1)
		exit(1);
	wrdestroy();
	exit(number);
}

/*
 ** Vide la memoire et renvoie le status
 ** Return [int] Status
*/

int			ft_exit(int ac, char **av, char **env)
{
	(void)env;
	if (ac >= 2)
	{
		if (ft_isnum(av[1]))
		{
			if (ac > 2)
			{
				ft_fprintf(2, "minishell: %s: too many arguments\n", av[0]);
				return (1);
			}
			ft_quit(ft_atoi(av[1]));
		}
		ft_fprintf(2, "minishell: %s: numeric argument required\n", av[0]);
		ft_quit(1);
	}
	ft_quit(0);
	return (1);
}
