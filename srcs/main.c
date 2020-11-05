#include <unistd.h>
#include <stdio.h>
#include <term.h>
#include "terminal.h"
#include "libft_mem.h"
#include "libft_printf.h"
#include "libft_string.h"
#include "minishell.h"

/*
 ** Vide la memoire et renvoie le status
 ** Return [int] Status
*/

int			ft_exit(int exit_status)
{
	wrdestroy();
	return (exit_status);
}

/*
 ** Renvoie un pointeur sur la structure du terminal
 ** Return [**t_term] structure du terminal
*/

t_term		**getterm(void)
{
	static t_term *term;

	return (&term);
}

/*
 ** Instancie une nouvelle ligne de commande
 ** Return [int] Status de reussite
*/

static int	new_cmd(t_term *term, t_block *copy)
{
	t_hash		*tmp;

	if (ft_strlen(copy->str_cmd) != 0)
	{
		if (!(tmp = ft_hashnew("h", copy)))
			return (ft_exit(EXIT_FAILURE));
		ft_hashadd_back(&term->historic, tmp);
		term->current_historic = NULL;
		ft_hashclear(&(term->list_blocks));
		if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
			return (ft_exit(EXIT_FAILURE));
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
 ** Gere la mise a jour du programme
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

static int	update(void)
{
	t_block		*copy;
	t_term	*term;

	term = *getterm();
	ft_printf("$ ");
	fflush(stdout);
	while (read(STDIN_FILENO, &(*getterm())->last_char, 1) > 0)
	{
		if (!(handle_key()))
		{
			put_cursor(term->cursor_pos, term->ndx_line);
			if (!(copy = ft_blockhashdup(term->list_blocks)))
				return (ft_exit(EXIT_FAILURE));
			ft_printf("%s", copy->str_cmd);
			(copy->str_cmd[0] != '\0') ? ft_printf("\n") : 0;
			get_pos();
			ft_printf("$ ");
			if (new_cmd(term, copy))
				return (ft_exit(EXIT_FAILURE));
			term->cursor_pos = PROMPT_SIZE;
			fflush(stdout);
			clear_eos(term, term->ndx_line);
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

	if (!(env = init_env(ac, av, environment)))
		return (EXIT_FAILURE);
	if (!((*getterm()) = wrmalloc(sizeof(t_term))))
		return (ft_exit(EXIT_FAILURE));
	if (init_term())
		return (ft_exit(EXIT_FAILURE));
	if (update())
		return (ft_exit(EXIT_FAILURE));
	if (tcsetattr(0, 0, &(*getterm())->termios_backup) == -1)
		return (ft_exit(EXIT_FAILURE));
	return (ft_exit(EXIT_SUCCESS));
}

