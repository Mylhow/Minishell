
#include "exec.h"

int main(int ac, char **av, char *envp[])
{
    (void)ac;
    (void)av;

    t_redirect  *redirection;
    redirection = malloc(sizeof(t_redirect));
    redirection->type = ">";
    redirection->file = "file";

    t_list      *l_redir;
    l_redir = ft_lstnew(redirection);

    exec_str(av + 1, l_redir, envp);

    free(l_redir);
    free(redirection);

    return (0);
}