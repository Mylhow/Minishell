/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:22:44 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 14:23:57 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# include "libft_ctype.h"
# include "libft_mem.h"
# include "libft_string.h"
# include "libft_printf.h"
# include "libft_number.h"
# include "sh_utils.h"
# include "environement.h"
# include <stdlib.h>
# include <unistd.h>

extern int	g_exit_status;

# define VAR_AMBIGUOUS	2
# define VAR_VALID 		1
# define VAR_NONE  		0

/*
**  EXPANDERS
*/

int		expand_var(char **dst, const char *str);
int		expand_word(t_cmd **dst, char *str);
int		expand_quotes(t_cmd *src);
int		expand_bslash(t_cmd *src);
int		expand_cmd(t_cmd **dst, char *simple_command);

#endif
