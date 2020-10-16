/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:08:04 by lrobino           #+#    #+#             */
/*   Updated: 2020/10/16 15:28:19 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <limits.h>
# include "libft.h"

/*
**  UTILS
*/

# define DEFAULT_PERM 0644

bool			is_builtin(char *str);
bool			file_exists(char *name);

/*
**  REDIRECTIONS UTILS
*/

# define NO_FILE -2

typedef struct	s_redirect
{
	char	*type;
	char	*file;
}				t_redirect;

int				redirect_stdout(char *file);
int				redirect_stdin(char *file);
int				append_stdout(char *file);

/*
**  EXEC
*/

int				exec_str(char **argv, t_list *l_redir, char **envp);

#endif
