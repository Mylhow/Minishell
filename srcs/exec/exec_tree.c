#include "exec.h"
#include "parsing.h"
#include "syntax_error.h"

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
