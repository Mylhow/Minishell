/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:30:29 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/11 11:24:27 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft_mem.h"
# include "libft_printf.h"
# include "unistd.h"
# include "terminal.h"
# include "environement.h"
# include "sh_utils.h"

int	ft_exit(int ac, char **av, char **env);
int	ft_echo(int ac, char **av, char **env);
int	ft_cd(int ac, char **av, char **env);
int	ft_pwd(int ac, char **av, char **env);
int	ft_env(int ac, char **av, char **env);
int	ft_export(int ac, char **av, char **env);
int	ft_unset(int ac, char **av, char **env);

#endif
