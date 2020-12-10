/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:24:35 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/10 15:54:37 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONEMENT_H
# define ENVIRONEMENT_H

# include <stdlib.h>
# include "libft_string.h"

extern char **g_envp;

int		load_env(char **envp);
char	*get_env(char *var);
int		add_var(char *name, char *value);
int		set_var(char *name, char *value);
int		del_var(char *name);

char	*concat_var(char *name, char *value);
char	**deconcat_var(char *var_line);
int		is_valid_var_name(char *var);

#endif
