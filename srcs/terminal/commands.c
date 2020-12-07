#include "terminal.h"
#include "libft_string.h"
#include "libft_printf.h"
#include "syntax_error.h"
#include <signal.h>
#include <stdio.h>

/*
 ** Prepare une nouvelle ligne de commande
 ** Return [int] Status de reussite
*/

static int	clear_new_cmd(t_term *term, t_block *copy, int sig)
{
	if (ft_strlen(copy->str_cmd) != 0)
	{
		if (sig != SIGINT)
			ft_histo_add(term, copy);
		term->current_historic = NULL;
		ft_hashclear(&(term->list_blocks));
		if (!(term->list_blocks = ft_hashnew("block_1", ft_blocknew())))
			return (EXIT_FAILURE);
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

int	new_cmd(t_term *term, int sig, int ret_handle)
{
	t_block *copy;

	if (put_cursor(term->cursor_pos, term->ndx_line) != 0)
		return (EXIT_FAILURE);
	if (!(copy = ft_blockhashdup(term->list_blocks)))
		return (EXIT_FAILURE);
	if (sig == SIGINT)
		ft_printf("^C");
	else if (ret_handle != NCMD_SYNTAX_ERROR){
		ft_printf("%s", term->str_ccmd);
	}
	else
		ft_printf("our bash : syntax error");
	(sig == SIGINT || term->str_ccmd[0] != '\0') ? ft_printf("\n") : 0;
	get_pos();
	ft_printf("$ ");
	if (clear_new_cmd(term, copy, sig))
		return (EXIT_FAILURE);
	term->cursor_pos = PROMPT_SIZE;
	fflush(stdout);
	clear_eos(term, term->ndx_line);
	return (EXIT_SUCCESS);
}

/*
 ** Gere le \n dans le block. Ajoute un block dans la structure.
 ** Return [int] Status de reussite
*/

int	ft_newline(t_term *term)
{
	t_hash	*hash;

	if (!(hash = ft_hashnew("block_", ft_blocknew())))
		return (EXIT_FAILURE);
	ft_hashadd_back(&(term->list_blocks), hash);
	term->ndx_line++;
	term->cursor_pos = PROMPT_SIZE;
	ft_printf("\n> ");
	term->current_block = hash;
	term->ndx_cursor = 0;
	return (PROCESS_SUCCESS);
}