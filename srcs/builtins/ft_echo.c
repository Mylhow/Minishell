#include "libft.h"
#include "libft_put.h"
#include "libft_string.h"
#include "libft_printf.h"

int ft_echo(int ac, char **av, char **env)
{
	int	i;
	int	j;
	int	new_line;

	(void) env;
	new_line = 1;
	i = 1;
	while (ac >= 2 && (av[i][0] == '-') && i < ac)
	{
		j = 1;
		while (av[i][j] == 'n')
			j++;
		if (j == 1 || av[i][j])
			break;
		new_line = (i == ac - 1) ? 1 : 0;
		i++;
	}
	while (i < ac - 1)
	{
		ft_putstr(av[i]);
		ft_putstr(" ");
		i++;
	}
	if (i < ac)
		ft_putstr(av[i]);
	if (new_line)
		ft_printf("\n");
	return (EXIT_SUCCESS);
}