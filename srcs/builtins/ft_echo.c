/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 12:23:58 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/16 12:28:56 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libft_put.h"
#include "libft_string.h"
#include "libft_printf.h"
#include "terminal.h"

int	is_new_line(int *index, int ac, char **av)
{
	int		new_line;
	int		i;
	int		j;

	i = 1;
	new_line = 1;
	while (ac >= 2 && i < ac && (av[i][0] == '-'))
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (j == 1 || av[i][j])
			break ;
		new_line = 0;
		i++;
	}
	*index = i;
	return (new_line);
}

int	ft_echo(int ac, char **av, char **env)
{
	int	i;
	int	new_line;

	(void)env;
	i = 1;
	new_line = is_new_line(&i, ac, av);
	while (i < ac)
	{
		ft_putstr(av[i]);
		if (i < ac - 1)
			ft_putstr(" ");
		i++;
	}
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}
