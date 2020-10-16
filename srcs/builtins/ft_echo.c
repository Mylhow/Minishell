#include "libft.h"
#include "libft_put.h"
#include "libft_string.h"
#include "minishell.h"

int ft_echo(int ac, char **av, char **env)
{
	int flag;
	int i;

	flag = 1;
	i = 1;
	(void) env;
	if (ac > 1)
	{
		if (!ft_strcmp(av[1], "-n") || !ft_strcmp(av[1], "--n"))
		{
			flag = 0;
			i = 2;
		}
		while (i < ac)
		{
			ft_putstr(av[i]);
			i++;
		}
		if (flag)
			ft_putchar('\n');
	}
	return (EXIT_SUCCESS);
}