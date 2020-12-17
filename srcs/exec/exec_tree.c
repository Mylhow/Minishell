/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 13:50:24 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/16 16:13:46 by lrobino          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parsing.h"
#include "syntax_error.h"
#include "environement.h"
#include "signal_manager.h"

static int	exec_piped_child(t_btree *child, int fd_pipe[2], int mode)
{
	close(fd_pipe[!mode]);
	dup2(fd_pipe[mode], mode);
	exec_tree(child);
	close(fd_pipe[mode]);
	exit(0);
}

int			handle_pipes(t_btree *l_child, t_btree *r_child)
{
	int		fd_pipe[2];
	int		pid_childs[2];

	if (pipe(fd_pipe) < 0)
		return (-1);
	if ((pid_childs[0] = fork()) < 0)
		ft_fprintf(STDERR_FILENO, "minishell: Fork error.\n");
	if (pid_childs[0] == 0)
		exec_piped_child(l_child, fd_pipe, 1);
	if ((pid_childs[1] = fork()) < 0)
		ft_fprintf(STDERR_FILENO, "minishell: Fork error.\n");
	if (pid_childs[1] == 0)
		exec_piped_child(r_child, fd_pipe, 0);
	if (waitpid(-1, &g_exit_status, 0) < 0)
		return (-1);
	close(fd_pipe[1]);
	close(fd_pipe[0]);
	if (waitpid(-1, &g_exit_status, 0) < 0)
		return (-1);
	return (0);
}

int			handle_operators(char *type, t_btree *l_child, t_btree *r_child)
{
	int	error;

	error = 0;
	if (ft_strncmp(type, ";", 1) == 0)
	{
		error += exec_tree(l_child);
		error += exec_tree(r_child);
	}
	else if (ft_strncmp(type, "&&", 2) == 0)
	{
		error += exec_tree(l_child);
		if (g_exit_status == 0)
			error += exec_tree(r_child);
	}
	else if (ft_strncmp(type, "||", 2) == 0)
	{
		error += exec_tree(l_child);
		if (g_exit_status != 0)
			error += exec_tree(r_child);
	}
	else if (ft_strncmp(type, "|", 1) == 0)
	{
		error += handle_pipes(l_child, r_child);
	}
	return (0);
}

int			exec_tree(t_btree *node)
{
	t_pretype	*pre;

	if (!node || g_interrupt)
		return (0);
	pre = (t_pretype *)node->content;
	if (pre->type == WORD)
	{
		if (exec_str((char *)pre->content) != 0)
			return (EXIT_FAILURE);
	}
	else if (pre->type == OPERAT)
	{
		if (handle_operators
((char *)pre->content, node->l_child, node->r_child) != 0)
			return (EXIT_FAILURE);
	}
	return (0);
}

int			exec_cmd(char *cmd)
{
	t_list	*op_tok;
	t_btree	*tree;

	op_tok = 0;
	tree = 0;
	g_interrupt = 0;
	if (!(op_tok = split_op_tok(cmd)))
		return (EXIT_FAILURE);
	if ((creation_btree(op_tok, &tree)) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (exec_tree(tree));
}
