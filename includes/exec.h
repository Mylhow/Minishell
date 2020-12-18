/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:08:04 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/18 11:18:28 by abourbou         ###   ########lyon.fr   */
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
int				handle_pipes(t_btree *l_child, t_btree *r_child);
int				handle_operators(char *type, t_btree *l_child,
												t_btree *r_child);
void			handle_sigquit(void);


#endif
