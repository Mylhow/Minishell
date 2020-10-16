#include "terminal.h"
#include "libft_printf.h"
#include "libft.h"

int	escape_sequences(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->last_char == '\033') {
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
		if (term->last_char == LEFTCHAR)
			move_left(block);
		else if (term->last_char == RIGHTCHAR)
			move_right(block);
		else if (term->last_char == UPCHAR)
			move_up(block);
		else if (term->last_char == DOWNCHAR)
			move_down(block);
		term->esc_flag = 0;
		return (2); //TODO pourquoi toujour renvoyer une valeur identique autre que FAILURE ou SUCCESSE?
	}
	return (EXIT_SUCCESS); //TODO pourquoi EXIT_SUCCESSE? EXIT_FAILURE plutot non?
}

int	backspace(t_block *block)//TODO comment faire du multi-lignes si on ne passe qu'une ligen a la fonction?
{
	t_term *term;
	int i;

	term = (*getTerm());
	i = -1;
	if (block->ndx_str > 0)
	{
		block->ndx_str--;
		while (block->ndx_str + ++i <= block->size)
			block->str_cmd[block->ndx_str + i] = block->str_cmd[block->ndx_str + i + 1];
		term->ndx_cursor--;
		block->size--;
		block->str_cmd[block->ndx_str + i + 1] = '\0';
		put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
		put_caps(T_CLEOL, 0);
		ft_printf("%s", block->str_cmd + block->ndx_str);
		put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
	}
	return (EXIT_SUCCESS);
}
