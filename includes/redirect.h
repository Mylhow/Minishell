/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:05:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/03 17:01:28 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# define NO_FILE        -2
# define DEFAULT_PERM   0644

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft_printf.h"
#include "libft_string.h"
#include "sh_utils.h"

extern int		g_stdin_backup;
extern int		g_stdout_backup;

int				backup_io(void);
int				redirect_stdout(char *file);
int				redirect_stdin(char *file);
int				append_stdout(char *file);

int             parse_redirections(t_cmd *cmd);
int				handle_redirection(t_list *l_redir);


#endif