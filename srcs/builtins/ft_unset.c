/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:44:43 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/11 15:27:09 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(int ac, char **av, char **envp)
{
	(void)envp;
	if (ac == 2)
	{
		if (is_valid_var_name(av[1], ft_strlen(av[1])) != 0)
		{
			ft_fprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier.\n", av[1]);
			return (0);
		}
		del_var(av[1]);
	}
	if (ac > 2)
		ft_fprintf(STDERR_FILENO, "minishell: unset: too many arguments.\n");
	return (0);
}
