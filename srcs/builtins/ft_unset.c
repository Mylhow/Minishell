/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:44:43 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 14:22:09 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_unset(int ac, char **av, char **envp)
{
	int	i;

	i = 1;
	(void)envp;
	while (i < ac)
	{
		if (is_valid_var_name(av[i], ft_strlen(av[i])) != 0)
		{
			ft_fprintf(STDERR_FILENO,
			"minishell: unset: `%s': not a valid identifier.\n", av[i]);
			return (1);
		}
		if (get_env(av[i]) != NULL)
			del_var(av[i]);
		if (get_env(ft_strjoin("declare -x ", av[i])) != NULL)
			del_var(ft_strjoin("declare -x ", av[i]));
		i++;
	}
	return (0);
}
