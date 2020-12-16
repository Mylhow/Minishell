/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:08:04 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 14:21:51 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include <signal.h>
# include "expander.h"
# include "redirect.h"
# include "parsing.h"

typedef int(*t_exec_builtin)(int, char **, char **);

/*
**  UTILS
*/

t_exec_builtin	is_builtin(char *str);
bool			file_exists(char *name);
bool			is_executable(char *file);
void			print_not_found(char *file);

/*
**  EXEC
*/

int				exec_str(char *cmd);
int				execbi(char *name, char **argv);
int				exec_cmd(char *cmd);
int				exec_tree(t_btree *node);

#endif
