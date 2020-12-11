#include "terminal.h"
#include "libft_printf.h"
#include "libft_mem.h"
#include "builtins.h"
#include "syntax_error.h"
#include "signal_manager.h"
#include "exec.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signal_main(int signal)
{
	if (signal == _EOF
	&& ((t_block *)(*getterm())->current_block->value)->size <= 0)
	{
		ft_printf("exit\n");
		ft_exit(0, 0, 0);
	}
	if (signal == SIGINT || signal == SIGQUIT)
		g_interrupt = 1;
}

void	signal_process(int signal)
{
	if (signal == SIGINT)
		exit(130);
	else if (signal == SIGQUIT)
		exit(131);
}

/*
 ** Gere la mise a jour du programme
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

static int	update(void)
{
	t_term	*term;
	int		ret;

	term = *getterm();
	ft_printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &term->last_char, 1) > 0)
	{
		(term->last_char == _EOF) ? signal_main(_EOF) : 0;
		ret = handle_key();
		if (!(ret) || ret == NCMD_SYNTAX_ERROR)
		{
			if (new_cmd(term, 0, ret))
				return (EXIT_FAILURE);
			continue;
		}
		fflush(stdout);
	}
	return (EXIT_SUCCESS);
}

// ft_env(ac -1, av + 1, (char**)env); // commande pour lancer ft_env avec les argument de minishell
// export(ac, av, (char **)env); // pareil pour export
// print_env(env); //affiche la table d'environnement
// add_env_var(envir *env, char* var); Pour ajouter une variable à l'environnement (attention c'est une copie de la variable qui est crée, pensez a free() l'original)

/*
 ** Fonctionne principal
 ** Return [int] Status de reussite
*/

char **g_env;

int			main(int ac, char **av, char **environment)
{
	signal(SIGINT, signal_main);
	signal(SIGQUIT, signal_main);
	//(*getenvironment()) = environment;
	load_env(environment);
	g_env = environment;
	if (!((*getterm()) = wrmalloc(sizeof(t_term))))
		return (ft_exit(ac, av, environment));
	if (init_term())
		return (ft_exit(ac, av, environment));
	if (update())
		return (ft_exit(ac, av, environment));
	if (tcsetattr(0, 0, &(*getterm())->termios_backup) == -1)
		return (ft_exit(ac, av, environment));
	return (ft_exit(ac, av, environment));
}

