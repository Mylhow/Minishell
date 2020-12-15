#include "exec.h"
#include "parsing.h"
#include "syntax_error.h"
#include "environement.h"
#include "signal_manager.h"

int handle_pipes(t_btree *l_child, t_btree *r_child)
{
    int     fd_pipe[2];
    int     pid_childs[2];

    if (pipe(fd_pipe) < 0)
        return (-1);
    if ((pid_childs[0] = fork()) < 0)
        printf ("Fork err\n");
    if (pid_childs[0] == 0)
    {
        close(fd_pipe[0]);
        dup2(fd_pipe[1], STDOUT_FILENO);
        exec_tree(l_child);
        close(fd_pipe[1]);
        exit(0);
    }
    if ((pid_childs[1] = fork()) < 0)
        printf ("Fork err\n");
    if (pid_childs[1] == 0)
    {
        close(fd_pipe[1]);
        dup2(fd_pipe[0], STDIN_FILENO);
        exec_tree(r_child);
        close(fd_pipe[0]);
        exit(0);
    }
    if (waitpid(-1, 0, 0) < 0)
        return (-1);
    close(fd_pipe[1]);
    close(fd_pipe[0]);
    if (waitpid(-1, 0, 0) < 0)
        return (-1);
    return (0);
}

int handle_operators(char *type, t_btree *l_child, t_btree *r_child)
{
    if (ft_strncmp(type, ";", 1) == 0)
    {
        exec_tree(l_child);
        exec_tree(r_child);
    }
    else if (ft_strncmp(type, "&&", 2) == 0)
    {
        exec_tree(l_child);
        if (g_exit_status == 0 )
            exec_tree(r_child);
    }
    else if (ft_strncmp(type, "||", 2) == 0)
    {
        exec_tree(l_child);
        if (g_exit_status != 0)
            exec_tree(r_child);
    }
    else if (ft_strncmp(type, "|", 1) == 0)
    {
        handle_pipes(l_child, r_child);
    }
    return (0);
}

int exec_tree(t_btree *node)
{
    t_pretype   *pre;

	if (!node || g_interrupt)
		return (0);
    pre = (t_pretype *)node->content;
    if (pre->type == WORD)
    {
        exec_str((char *)pre->content);
        return (0);
    }
    else if (pre->type == OPERAT)
    {
        handle_operators((char *)pre->content, node->l_child, node->r_child);
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
	g_interrupt = 0;
	if (!(op_tok = split_op_tok(cmd)))
		return EXIT_FAILURE;
	if ((creation_btree(op_tok, &tree)) == EXIT_FAILURE)
		return EXIT_FAILURE;
	return exec_tree(tree);
}
