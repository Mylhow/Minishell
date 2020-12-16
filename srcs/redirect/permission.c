
#include "redirect.h"
#include <errno.h>

int check_permissions(char *file)
{
    if (open(file, O_RDWR, DEFAULT_PERM) < 0)
    {
        ft_fprintf(STDERR_FILENO, "minishell: %s: %s.\n", file, strerror(errno));
        return (-1);
    }
    return (0);
}

int is_file(char *file)
{
    struct stat st;

    if (stat(file, &st) != 0)
        return (0);
    return (1);
}