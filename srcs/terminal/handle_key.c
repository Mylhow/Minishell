#include "terminal.h"

//handle escape sequences like arrows
int     escape_sequences(t_term *term)
{
	if (term->last_char == '\033')
	{
		// dprintf(1, "ESC");
		term->esc_flag = 1;
		return 1;
	}
	else if (term->esc_flag == 1 && term->last_char == '[')
	{
		term->esc_flag = 2;
		return 1;
	}
	else if (term->esc_flag == 2)
	{
		//séquence d'échappement
		if (term->last_char == 'A')
		{
			// arrow up
			if (term->ndx_str / term->caps.column > 1)
			{ 
				term->ndx_str -= term->caps.column;
				term->ndx_line -= 1;
				tputs(term->caps.up, 1, ft_m_putchar);
			}
		}
		if (term->last_char == 'B')
		{
			//arrow down
			if (term->ndx_str / term->caps.column < term->str_size / term->caps.column)
			{
				//si nous ne somme pas sur la derniere ligne
				tputs(term->caps.down, 1, ft_m_putchar);
			}
		}
		if (term->last_char == 'C')
		{
			//arrow right
			if (term->ndx_str < term->str_size)
			{
				if (term->ndx_cursor < term->caps.column)
				{
					term->ndx_cursor++;
					tputs(term->caps.right, 1, ft_m_putchar);
				}
				else
				{
					//si on atteint le bout de la ligne
					term->ndx_cursor = 0;
					term->ndx_line += 1;
					tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
				}
				
				term->ndx_str++;
			}
		}
		if (term->last_char == 'D')
		{
			//arrow left
				// dprintf(1, "cursor =%d", term->ndx_cursor);
			if (term->ndx_str > 0)
			{
				if (term->ndx_cursor > 0)
				{
					term->ndx_cursor--;
					tputs(term->caps.left, 1, ft_m_putchar);
				}
				else
				{
					//si on atteint le bout de la ligne
					term->ndx_cursor = term->caps.column;
					term->ndx_line -= 1;
					tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
					// debug(term);
				}
				term->ndx_str--;
			}
		}
		term->esc_flag = 0;
		return 1;
	}
	return 0;
}
//handle the suppression of a caractere
int     back_space(t_term *term)
{
	int i;

	i = 0;
	if (term->ndx_str > 0)
	{
		term->ndx_str--;
		while (term->ndx_str + i <= term->str_size)
		{
			// dprintf(1, "char = %c\n", term->str_cmd[term->ndx_str + i]);
			term->str_cmd[term->ndx_str + i] = term->str_cmd[term->ndx_str + i + 1];
			i++;
		}
		term->ndx_cursor--;
		term->str_size--;
		term->str_cmd[term->ndx_str + i + 1] = '\0';
		tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
		tputs(term->caps.cl_eol, 1, ft_m_putchar);
		dprintf(1, "%s", term->str_cmd + term->ndx_str);
		tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
	}
	// debug(term);
	return 1;
}
// insére un caractere dans str_cmd
void	insert(t_term *term)
{
	int i;

	i = 0;
	while (term->str_size - i > term->ndx_str)
	{
		// dprintf(1, "i = %d", i);
		term->str_cmd[term->str_size -i] =  term->str_cmd[term->str_size -1 - i]; //deplace un caractere d'un cran vers la droite (en memoire)
		i++;
	}
	term->str_cmd[term->ndx_str] = term->last_char; //insere le nouveau caractere
	if (term->ndx_cursor >= term->caps.column - PROMPT_SIZE)
	{
		//si on arrive a la fin du terminal
		term->ndx_cursor = 0;
		term->ndx_line += 1;
		dprintf(1, "\n");
	}
	tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
	dprintf(1, "%s", term->str_cmd + term->ndx_str);
	term->ndx_cursor++;
	tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
	term->ndx_str++;
	term->str_size++;
}

//return 1 if continue
//return 0 if end of cmd
int		handle_key(t_term *term)
{


	// IDéE:: 
	//	enlever écriture des \n sur le multilignes, save pos écrit fin de phrase, restore pos
	//
	// erreur: Pour chaque block, un espace de trop apparait
	//
	// a chaque commande récuperer de nouveau les parametres du terminal.
	//
	//gérer le retour a la ligne
	// char num[25];

	// dprintf(0, "\033[6n");
	// dprintf(0, "read:%ld", read(0, num, 24));
	// num[4] = '\0';
	// dprintf(1, ";%d;", term->ndx_line);
	// term->ndx_line = ft_atoi(num+2);
	// term->ndx_line --;
	// // dprintf(1, "ndx_line = %d", term->ndx_line);
	// tputs(tgoto(term->caps.pos, term->ndx_cursor, term->ndx_line), 1, ft_m_putchar);
	// debug(term);
	// debug(term);
	if (term->ndx_line > term->caps.line - 1)
		term->ndx_line = term->caps.line - 1;
	if (term->last_char == '\033' || term->esc_flag == 1 || term->esc_flag == 2)
		return(escape_sequences(term));
	//gestion du retour
	else if ((term->last_char == 127 || term->last_char == 8))
		return (back_space(term));
	//gestion des caracteres tapés
	else if (term->last_char != '\n' )
	{
		//réalloue la string si elle est trop petite
		if (term->ndx_str == STR_SIZE * term->nb_blocks - 1)
		{
			term->str_cmd = resize_str(term->str_cmd, (term->nb_blocks + 1) * STR_SIZE);
			term->nb_blocks++;
		}
		//enregistrement du caractere
		insert(term);
		//affichage du caractere
		return 1;
	}
	// dprintf(1, "ENTER");
	//si on passe ici ENTER a été pressé
	if (term->str_cmd[0] != '\0' && term->last_char == '\n')
		dprintf(1, "\n");
	term->ndx_cursor = 0;
	term->ndx_str = 0;
	term->str_size = 0;
	term->ndx_line += 1;
	return 0;
}