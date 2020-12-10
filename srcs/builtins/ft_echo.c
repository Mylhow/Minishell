#include "libft.h"
#include "libft_put.h"
#include "libft_string.h"

int ft_echo(int ac, char **av, char **env)
{
	int i;
	int	new_line;

	(void) env;
	new_line = 1;
	i = 1;
	if (ac >= 2 && !ft_strcmp(av[1], "-n"))
	{
		new_line = 0;
		i++;
	}
	while (i < ac - 1)
	{
		ft_putstr(av[i]);
		ft_putstr(" ");
		i++;
	}
	ft_putstr(av[i]);
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}