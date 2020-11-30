#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include "terminal.h"
#include "libft_mem.h"
#include "libft_printf.h"
#include "libft_string.h"
#include "minishell.h"
#include <signal.h>


/*
 ** Prepare une nouvelle ligne de commande
 ** Return [int] Status de reussite
*/

static int	clear_new_cmd(t_term *term, t_block *copy, int sig)
{
	t_hash		*tmp;

	if (ft_strlen(copy->str_cmd) != 0)
	{
		if (sig != SIGINT)
		{
			if (!(tmp = ft_hashnew("h", copy)))
				return (ft_exit(0, 0, 0));
			ft_hashadd_back(&term->historic, tmp);
		}
		term->current_historic = NULL;
		ft_hashclear(&(term->list_blocks));
		if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
			return (ft_exit(0, 0, 0));
		term->current_block = term->list_blocks;
		term->original_line = term->ndx_line;
	}
	else
	{
		term->original_line += 1;
		term->cursor_pos = 0;
	}
	return (EXIT_SUCCESS);
}

/*
 ** Instancie une nouvelle ligne de commande
 ** Return [int] Status de reussite
*/

static int	new_cmd(t_term *term, int sig, int ret_handle)
{
	t_block		*copy;

	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	if (!(copy = ft_blockhashdup(term->list_blocks)))
		return (ft_exit(0, 0, 0));
	if (sig == SIGINT)
		ft_printf("^C");
	else if (ret_handle != EXIT_SYNTAX_ERROR){
		ft_printf("%s", copy->str_cmd);
	}
	else
		ft_printf("%s", "our bash : syntax error");
	(sig == SIGINT || copy->str_cmd[0] != '\0') ? ft_printf("\n") : 0;
	get_pos();
	ft_printf("$ ");
	if (clear_new_cmd(term, copy, sig))
		return (ft_exit(0, 0, 0));
	term->cursor_pos = PROMPT_SIZE;
	fflush(stdout);
	clear_eos(term, term->ndx_line);
	return (EXIT_SUCCESS);
}

void signal_manager(int signal)
{
	if (signal == _EOF
	&& ((t_block *)(*getterm())->current_block->value)->size <= 0)
	{
		ft_printf("exit\n");
		ft_exit(0, 0, 0);
	}
	else if (signal == SIGINT)
	{
		if (new_cmd(*getterm(), signal, 0))
		{
			ft_exit(0, 0, 0);
		}
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
	while (read(STDIN_FILENO, &term->last_char, 1) > 0)
	{
		(term->last_char == _EOF) ? signal_manager(_EOF) : 0;
		ret = handle_key();
		if (!(ret) || ret == 3)
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
int			main(int ac, char **av, char **environment)
{
	envir       *env;

	signal(SIGINT, signal_manager);
	if (!(env = init_env(ac, av, environment)))
		return (EXIT_FAILURE);
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

