/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:05:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 11:57:05 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# define NO_FILE        -2
# define DEFAULT_PERM   0644

# define F_PERMOK       0
# define F_TOLONG       1
# define F_ACCESSDENY   2
# define F_NOTFOUD      3
# define F_DIRECTORY    4

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/param.h>
#include "libft_printf.h"
#include "libft_string.h"
#include "sh_utils.h"
#include <errno.h>
#include <string.h>

# define    M_STDIN     0
# define    M_STDOUT    1
# define    M_FULLIO    2

int				backup_io(int mode);
int				restore_io(int mode);

int				redirect_stdout(char *file);
int				redirect_stdin(char *file);
int				append_stdout(char *file);

int             parse_redirections(t_cmd *cmd);
int				handle_redirection(t_list *l_redir);

int             check_permissions(char *file);
int             is_file(char *file);

#endif