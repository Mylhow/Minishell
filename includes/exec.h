/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:08:04 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/04 18:39:52 by lrobino          ###   ########lyon.fr   */
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

# include "expander.h"
# include "redirect.h"

/*
**  UTILS
*/

bool			is_builtin(char *str);
bool			file_exists(char *name);

/*
**  EXEC
*/
int				exec_str(char *cmd, char **envp);

int exec_cmd(char *cmd);

#endif
