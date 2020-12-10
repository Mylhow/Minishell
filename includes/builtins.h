/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 11:30:29 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/10 13:51:10 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "terminal.h"
# include "env.h"


int	ft_exit(int ac, char **av, char **env);
int	ft_echo(int ac, char **av, char **env);
int	ft_cd(int ac, char **av, char **env);
int	ft_pwd(int ac, char **av, char **env);
#endif
