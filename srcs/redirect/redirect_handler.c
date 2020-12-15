/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:15:06 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 13:59:08 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"
#include "libft_mem.h"

/*
**  CREATE_REDIRECTION
**  creates redirection based on type ("<" ">" ">>") to a filename
*/

static t_redirect   *create_redirection(char *type, char *filename)
{
    t_redirect  *redir;

    if (is_redirect(type))
    {
        if (!(redir = wrmalloc(sizeof(*redir))))
            return (NULL);
        redir->file = filename;
        redir->type = type;
        return (redir);
    }
    return (NULL);
}


int     check_first_redirect(t_cmd *cmd, t_list *argv)
{
    char        *info_buff[2];
    t_redirect  *redir;
    t_list      *next;

    if (!argv || !argv->next)
        return (1);
    info_buff[0] = (char *)argv->content;
    info_buff[1] = (char *)argv->next->content;
    if ((redir = create_redirection(info_buff[0], info_buff[1])))
    {
        cmd->l_redir = ft_lstnew(redir);
        next = argv->next->next;
        if (next)
            cmd->l_argv = next;
        else
            cmd->l_argv = NULL;
        wrfree(argv->next);
        wrfree(argv);
    }
    return (0);
}

/*
**  PARSE_REDIRECTIONS
**  Parses redirections in argv of cmd
*/
#include <stdio.h>

int     parse_redirections(t_cmd *cmd)
{
    t_list      *argv;
    t_list      *next_tok;
    t_redirect  *redirect_buff;
    char        *info_buff[2];

    cmd->l_redir = 0;
    check_first_redirect(cmd, cmd->l_argv);
    argv = cmd->l_argv;
    while (argv && argv->next && argv->next->next)
    {
        info_buff[0] = (char *)argv->next->content;
        info_buff[1] = (char *)argv->next->next->content;
       // printf ("info_buffs : [%s] [%s]\n", info_buff[0], info_buff[1]);
        if ((redirect_buff = create_redirection(info_buff[0], info_buff[1])))
        {
            if (!(cmd->l_redir))
                cmd->l_redir = ft_lstnew(redirect_buff);
            else
                ft_lstadd_back(&cmd->l_redir, ft_lstnew(redirect_buff));
            next_tok = argv->next->next->next;
            wrfree(argv->next->next);
            wrfree(argv->next);
            argv->next = next_tok;
        }
        else
            argv = argv->next;
    }
    return (0);
}

/*
**	Handles list of I/O redirections as t_list ( must have: t_list.content: typeof(t_redirect *) )
*/
int				handle_redirection(t_list *l_redir)
{
	t_redirect	*redirect;

	while (l_redir)
	{
		redirect = (t_redirect *)l_redir->content;
		if ((ft_strcmp(redirect->type, ">") == 0)
            && (redirect_stdout(redirect->file) != 0))
				return (1);
		else if ((ft_strcmp(redirect->type, ">>") == 0)
			&& (append_stdout(redirect->file) != 0))
				return (1);
		else if ((ft_strcmp(redirect->type, "<") == 0)
			&& (redirect_stdin(redirect->file) != 0))
				return (1);
		l_redir = l_redir->next;
	}
	return (0);
}
