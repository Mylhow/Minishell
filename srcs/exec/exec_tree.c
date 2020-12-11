#include "exec.h"
#include "parsing.h"
#include "syntax_error.h"
#include "environement.h"

int exec_tree(t_btree *node, char **envp);

int handle_pipes(t_btree *l_child, t_btree *r_child, char **envp)
{
    int pids[2];
    int fd_pipe[2];

    if ((pids[0] = fork()) < 0)
        return (-1);
    else if (pids[0] == 0)
    {
        if (pipe(fd_pipe) < 0)
            return (-1);
        if ((pids[1] = fork()) < 0)
            return (-1);
        else if (pids[1] == 0)
        {
            close(fd_pipe[0]);
            dup2(fd_pipe[1], STDOUT_FILENO);
            exec_tree(l_child, envp);
            close(fd_pipe[1]);
            exit (0);
        }
        else if (waitpid(pids[1], 0, 0) < 0)
            return (-1);
        close(fd_pipe[1]);
        dup2(fd_pipe[0], STDIN_FILENO);
        exec_tree(r_child, envp);
        close(fd_pipe[0]);
        exit (g_exit_status);
    }
    else if (waitpid(pids[0], &g_exit_status, 0) < 0)
        return (-1);
    return (0);
}

int handle_operators(char *type, t_btree *l_child, t_btree *r_child, char **envp)
{
    if (ft_strncmp(type, ";", 1) == 0)
    {
        exec_tree(l_child, envp);
        exec_tree(r_child, envp);
    }
    else if (ft_strncmp(type, "&&", 2) == 0)
    {
        exec_tree(l_child, envp);
        if (g_exit_status == 0)
            exec_tree(r_child, envp);
    }
    else if (ft_strncmp(type, "||", 2) == 0)
    {
        exec_tree(l_child, envp);
        if (g_exit_status != 0)
            exec_tree(r_child, envp);
    }
    else if (ft_strncmp(type, "|", 1) == 0)
    {
        handle_pipes(l_child, r_child, envp);
    }
    return (0);
}

int exec_tree(t_btree *node, char **envp)
{
    t_pretype   *pre;

	if (!node)
		return (0);
    pre = (t_pretype *)node->content;
    if (pre->type == WORD)
    {
        exec_str((char *)pre->content, envp);
        return (0);
    }
    else if (pre->type == OPERAT)
    {
        handle_operators((char *)pre->content, node->l_child, node->r_child, envp);
        return (0);
    }
    return (0);
}


//! to erase, test function for split_op_tok
void	print_list(t_list *t_op_tok)
{
	t_list		*current;
	t_pretype	*current_pret;

	current = t_op_tok;
	while (current)
	{
		current_pret = current->content;
		if (current_pret->type != PARENTH)
			ft_printf("type : [%d], content : [%s]\n", current_pret->type, (char *)current_pret->content);
		else
		{
			ft_printf("******into parenth *******\n");
			print_list(current_pret->content);
			ft_printf("******end parenth *******\n");
		}
		current = current->next;
	}
}

int exec_cmd(char *cmd)
{
	t_list *op_tok;
	t_btree *tree;

	op_tok = 0;
	tree = 0;
	if (!(op_tok = split_op_tok(cmd)))
		return EXIT_FAILURE;
	if ((creation_btree(op_tok, &tree)) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return exec_tree(tree, g_envp);
}
