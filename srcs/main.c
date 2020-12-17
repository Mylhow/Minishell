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
	t_term *term;

	term = (*getterm());
	if (signal == _EOF
	&& ((t_block *)term->current_block->value)->size <= 0)
	{
		ft_printf("exit\n");
		ft_exit(0, 0, 0);
	}
	if (signal == SIGINT || signal == SIGQUIT)
	{
		g_interrupt = 1;
		fflush(stdout);

		term->ndx_line = term->original_line + (((t_block *)term->current_block->value)->size + PROMPT_SIZE) / term->nb_cols + 1;
		term->ndx_cursor = 0;
		term->cursor_pos = PROMPT_SIZE;
		if (term->ndx_line > term->nb_lines - 1)
		{
			if (!g_passed)
			{
				put_cursor(0, term->ndx_line);
				ft_printf("\n");
			}
			term->ndx_line = term->nb_lines - 1;
		}
		if (!g_passed)
			ft_printf("^C");
		if (put_cursor(0, term->ndx_line) != 0)
			return;
		term->current_historic = NULL;
		ft_hashclear(&(term->list_blocks));
		if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
			return ;
		term->current_block = term->list_blocks;
		term->original_line = term->ndx_line;
		if (!g_passed)
			ft_printf("$ ");
	}
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
	while ((read(STDIN_FILENO, &term->last_char, 1) > 0))
	{
        (term->last_char == _EOF) ? signal_main(_EOF) : 0;
		ret = handle_key();
		if (!(ret) || ret == NCMD_SYNTAX_ERROR)
		{
			//ft_printf("from updqte");
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

