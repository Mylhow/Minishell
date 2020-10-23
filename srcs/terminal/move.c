#include "terminal.h"
#include "libft_string.h"
#include "libft_printf.h"

void     move_right(t_block *block)
{
	t_term *term;

	term = (*getTerm());
	if (term->ndx_cursor < block->size)
	{
		term->ndx_cursor++;
		term->cursor_pos++;
		if (term->cursor_pos == term->nb_cols)
		{
			term->cursor_pos = 0;
			term->ndx_line++;
			block->delta_end_line--;
		}
	}
}

void     move_left(t_block *block)
{
    t_term *term;

    term = (*getTerm());
	if (term->ndx_cursor > 0)
	{
    	term->ndx_cursor--;
		term->cursor_pos--;
		if (term->cursor_pos < 0)
		{
			term->cursor_pos = term->nb_cols - 1;
			term->ndx_line--;
			block->delta_end_line++;
		}
	}
}

int		print_historic(t_term *term, t_block *block)
{
	char	*current;

	current = (char *)term->current_historic->value;
	term->ndx_line -= block->nb_blocks - 1;
	term->cursor_pos = PROMPT_SIZE;
	put_cursor(term->cursor_pos, term->ndx_line);
	clear_eos(term);
	if (!(block->str_cmd = ft_strdup(current))) //TODO leaks
			return (EXIT_FAILURE);
	block->size = ft_strlen(block->str_cmd);
	block->nb_blocks = (block->size + PROMPT_SIZE) / term->nb_cols + 1;
	block->alloc_size = (term->nb_cols * block->nb_blocks) + 1 - PROMPT_SIZE;
	ft_printf("%s", current);
	term->cursor_pos = (block->size + PROMPT_SIZE) % term->nb_cols;
	term->ndx_cursor = block->size;
	term->ndx_line += block->nb_blocks - 1;
	if (term->ndx_line > term->nb_lines - 1)
		term->ndx_line = term->nb_lines - 1;
	put_cursor(term->cursor_pos, term->ndx_line);
	return(EXIT_SUCCESS);
}

int     move_up(t_term *term, t_block *block)
{
	int		flag;

	flag = 0;
	if (!term->historic)
		return (EXIT_SUCCESS);
	else if (!term->current_historic)
	{
		if ((term->current_historic = term->historic->last(term->historic)))
		{
			flag = 1;
		}
	}
	else if (term->current_historic->before)
	{
		term->current_historic = term->current_historic->before;
		flag = 2;
	}
//TODO tester avec un texte plus grand que le screen entier + avec défilement de l'historique
	if (flag) //si il y a un up
		return(print_historic(term, block));
	return (EXIT_SUCCESS);
}
//TODO faire move_down
//TODO faire en sorte que move down fasse revenir au texte initial et non juste au dernier historique
int     move_down(t_term *term, t_block *block)
{
	int		flag;

	flag = 0;
	if (!term->historic)
		return (EXIT_SUCCESS);
	else if (term->current_historic && term->current_historic->next)
	{
		term->current_historic = term->current_historic->next;
		flag = 2;
	}
//TODO tester avec un texte plus grand que le screen entier + avec défilement de l'historique
//TODO effacer les doublons cote a cote dans l'historiqe
//TODO effacer les historiques vides
	if (flag) //si il y a un up
		return(print_historic(term, block));
	return (EXIT_SUCCESS);
}
