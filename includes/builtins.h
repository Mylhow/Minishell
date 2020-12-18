/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:43:35 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:43:40 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "libft_ctype.h"
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

/*
** put pwd into str
** origin_fct : fct where this function is executed (it is for error case)
** return 0 if it works or 1 if error
*/
int	ft_get_pwd(char *origin_fct, char **str);

#endif
