/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:18:59 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/03 17:33:50 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SH_UTILS_H
# define SH_UTILS_H

# include <sys/types.h>
# include "libft_list.h"

typedef struct	s_redirect
{
	char	*type;
	char	*file;
}				t_redirect;

typedef struct  s_cmd
{
	t_list      *l_argv;
    t_list      *l_redir; // <t_redirect>
}               t_cmd;

/*
**	Shell quotes handler.
*/

# define QUOTE_NONE     '\0'
# define QUOTE_SINGLE   '\''
# define QUOTE_DOUBLE   '\"'
# define QUOTE_RESET    "QRESET_MS"

char    get_quotes(char *current);

char	*replace_section
	(char *str, int index, const char *replace, size_t pattern_len);

int		parse_argv(char ***argv, t_list	*l_argv);

char	is_redirect(char *c);
char	is_ifs(char c);
int		contains_ifs(char *str);

#endif