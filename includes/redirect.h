/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:05:27 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/04 14:00:36 by lrobino          ###   ########lyon.fr   */
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

int				backup_io(void);
int				restore_io(void);
int				redirect_stdout(char *file);
int				redirect_stdin(char *file);
int				append_stdout(char *file);

int             parse_redirections(t_cmd *cmd);
int				handle_redirection(t_list *l_redir);


#endif