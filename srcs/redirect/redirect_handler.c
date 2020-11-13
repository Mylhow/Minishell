/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:15:06 by lrobino           #+#    #+#             */
/*   Updated: 2020/11/12 19:33:55 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirect.h"


static t_redirect   *create_redirection(char *type, char *filename)
{
    t_redirect  *redir;

    if (is_redirect(type))
    {
        if (!(redir = malloc(sizeof(*redir))))
            return (NULL);
        redir->file = filename;
        redir->type = type;
        return (redir);
    }
    return (NULL);
}

int     parse_redirections(t_cmd *cmd)
{
    t_list      *argv;
    t_list      *next_tok;
    t_redirect  *redirect_buff;
    char        *info_buff[2];
    int         list_created;

    list_created = 0;
    argv = cmd->l_argv;
    while (argv && argv->next && argv->next->next)
    {
        info_buff[0] = (char *)argv->next->content;
        info_buff[1] = (char *)argv->next->next->content;
        if ((redirect_buff = create_redirection(info_buff[0], info_buff[1])))
        {
            if (!list_created)
            {
                cmd->l_redir = ft_lstnew(redirect_buff);
                list_created = 1;
            }
            else
                ft_lstadd_back(&cmd->l_redir, ft_lstnew(redirect_buff));
            next_tok = argv->next->next->next;
            free(argv->next->next);
            free(argv->next);
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
            && (redirect_stdout(redirect->file) < 0))
				return (-1);
		else if ((ft_strcmp(redirect->type, ">>") == 0)
			&& (append_stdout(redirect->file) < 0))
				return (-1);
		else if ((ft_strcmp(redirect->type, "<") == 0)
			&& (redirect_stdin(redirect->file) == -2))
				return (NO_FILE);
		l_redir = l_redir->next;
	}
	return (1);
}
