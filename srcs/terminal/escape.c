#include "terminal.h"
#include "libft_printf.h"
#include "libft_mem.h"
#include "libft_string.h"
#include <unistd.h>

/*
 ** Manage les sequences des fleches
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

static int	move_manage(t_term *term, t_block *block)
{
	if (term->last_char == LEFTCHAR)
		move_left();
	else if (term->last_char == RIGHTCHAR)
		move_right(block);
	else if (term->last_char == UPCHAR && move_up(term))
		return (EXIT_FAILURE);
	else if (term->last_char == DOWNCHAR && move_down(term))
		return (EXIT_FAILURE);
	else if (term->last_char == HOMECHAR)
	{
		term->ndx_line = term->original_line;
		term->ndx_cursor = 0;
		term->cursor_pos = PROMPT_SIZE;
	}
	else if (term->last_char == ENDCHAR)
	{
		term->ndx_line = (block->size / term->nb_cols) + term->original_line;
		term->ndx_cursor = block->size;
		term->cursor_pos = block->size % term->nb_cols + PROMPT_SIZE;
	}
	put_cursor(term->cursor_pos, term->ndx_line);
	term->esc_flag = 0;
	return (EXIT_SUCCESS);
}

/*
 ** Manage les sequences CTRL
 ** Return [int] Statue de reussite
 ** TODO Ajoute les check de ctrl_right et ctrl_left
*/

static int	ctrl_manage(t_term *term, t_block *block, char my_char)
{
	if (my_char == 'A')
		ctrl_up(term);
	else if (my_char == 'B')
		ctrl_down(term, block);
	else if (my_char == 'C')
		ctrl_right(term, block);
	else if (my_char == 'D')
		ctrl_left(term, block);
	put_cursor(term->cursor_pos, term->ndx_line);
	term->esc_flag = 0;
	return (EXIT_SUCCESS);
}

/*
 ** Manage la sequence d'echappement
 ** Return [int] Status de reussite
 ** TODO Reduire la taille de cette fonction
 ** TODO Ajout de return check ctrl_manage
*/

int			escape_sequences(t_block *block)
{
	t_term	*term;
	char	my_char;

	term = (*getterm());
	if (term->last_char == '\033')
	{
		term->esc_flag = 1;
		return (2);
	}
	else if (term->esc_flag == 1 && term->last_char == '[')
	{
		term->esc_flag = 2;
		return (2);
	}
	else if (term->esc_flag == 2)
	{
		if (term->last_char == '1')
			term->esc_flag = 3;
		else
		{
			if (move_manage(term, block))
				return (EXIT_FAILURE);
		}
		return (2);
	}
	else if (term->esc_flag == 3)
	{
		read(STDIN_FILENO, &my_char, 1);
		if (my_char == '2') //TODO 2 pour mac 5 pour linux
		{
			// TODO: réécriture de la fin de la chaine de caractere
			// TODO: il doit y avoir un \n quelque part à catch
			read(STDIN_FILENO, &my_char, 1);
			ctrl_manage(term, block, my_char);
			return (2);
		}
	}
	return (EXIT_SUCCESS);
}

/*
 ** Permet de supprimer un caractere avec backspace
 ** Return [int] Status de reussite
 ** TODO Check return term-fonction
*/

int			backspace(t_block *block)
{
	t_term	*term;
	char	*tmp;

	term = (*getterm());
	if (block->size > 0 && term->ndx_cursor > 0)
	{
		term->cursor_pos--;
		term->ndx_cursor--;
		tmp = ft_strdup(block->str_cmd);
		ft_bzero(block->str_cmd, block->size);
		ft_memcpy(block->str_cmd, tmp, term->ndx_cursor);
		ft_strcat(block->str_cmd, tmp + term->ndx_cursor + 1);
		put_cursor(term->cursor_pos, term->ndx_line);
		put_caps(T_CLEOL, 0);
		ft_printf("%s", block->str_cmd + term->ndx_cursor);
		block->size--;
		if (term->cursor_pos < 0)
		{
			term->cursor_pos = term->nb_cols - 1;
			term->ndx_line--;
		}
		put_caps(T_CLEOL, 0);
	}
	put_cursor(term->cursor_pos, term->ndx_line);
	return (EXIT_SUCCESS);
}
