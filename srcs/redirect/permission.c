
#include "redirect.h"

int check_permissions(char *file)
{
    struct stat st;

    if (ft_strlen(file) > PATH_MAX)
    {
		ft_fprintf(STDERR_FILENO, "minishell: %s: Filename too long.\n", file);
        return (F_TOLONG);
    }
	if (stat(file, &st) == -1)
    {
        ft_fprintf(STDERR_FILENO, "minishell: %s: File not found\n", file);
		return (F_NOTFOUD);
    }
	if (S_ISDIR(st.st_mode))
    {
		ft_fprintf(STDERR_FILENO, "minishell: %s: Is a directory.\n", file);
        return (F_DIRECTORY);
    }
	if (!(st.st_mode & S_IRUSR))
    {
		ft_fprintf(STDERR_FILENO, "minishell: %s: Permission denied.\n", file);
        return (F_ACCESSDENY);
    }
    return (F_PERMOK);
}

int is_file(char *file)
{
    struct stat st;

    if (stat(file, &st) != 0)
        return (0);
    return (1);
}