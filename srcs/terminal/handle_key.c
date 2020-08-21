#include "terminal.h"

//return 1 if continue
//return 0 if end of cmd
int		handle_key(t_term *term)
{
       // int x = term.last_char;
        // dprintf(1, "x = %d", x);
    if (term->esc_flag == 2)
    {
        if (term->last_char == 'A')
        {
            if (term->ndx_str > term->caps.column)
            { 
                term->ndx_str -= term->caps.column;
                tputs(term->caps.up, 1, ft_m_putchar);
            }
        }
        if (term->last_char == 'B')
            tputs(term->caps.down, 1, ft_m_putchar);
        if (term->last_char == 'C')
            tputs(term->caps.right, 1, ft_m_putchar);
        if (term->last_char == 'D')
        {
                //fleches gauche
                // dprintf(1, "cursor =%d", term->ndx_cursor);
            if (term->ndx_cursor > 0)
            {
                term->ndx_cursor--;
                tputs(term->caps.left, 1, ft_m_putchar);
            }
            if (term->ndx_str > 0)
                term->ndx_str--;
        }
        term->esc_flag = 0;
        return 1;
    }
    else if (term->esc_flag == 1 && term->last_char == '[')
    {
        term->esc_flag = 2;
        return 1;
    }
    else if (term->last_char == '\033')
    {
        term->esc_flag = 1;
        return 1;
    }
        //gestion du retour
    else if ((term->last_char == 127 || term->last_char == 8) && term->ndx_cursor > 0)
    {
        term->str_cmd[term->ndx_str - 1] = '\0';
        tputs(tgoto(term->caps.pos, term->ndx_cursor + 1, term->ndx_line), 1, ft_m_putchar);
        tputs(term->caps.cl_eol, 1, ft_m_putchar);
        term->ndx_cursor--;
        term->ndx_str--;
        return 1;
    }
        //gestion des caracteres tapés
    else if (term->last_char != '\n' )
    {
            //si la string aloué est trop petite
        if (term->ndx_str >= STR_SIZE * term->nb_blocks)
        {
            term->str_cmd = resize_str(term->str_cmd, (term->nb_blocks + 1) * STR_SIZE);
            term->nb_blocks++;
        }
            //enregistrement du caractere
        term->str_cmd[term->ndx_str] = term->last_char;
        term->ndx_cursor++;
        term->ndx_str++;
            //affichage du caractere
        if (term->ndx_cursor >= term->caps.column - PROMPT_SIZE)
        {
                //si on arrive a la fin du terminal
            term->ndx_cursor = 0;
            term->ndx_line += 1;
            dprintf(1, "\n");
        }
        tputs(tgoto(term->caps.pos, term->ndx_cursor + PROMPT_SIZE, term->ndx_line), 1, ft_m_putchar);
    	dprintf(1, "%s", term->str_cmd + term->ndx_str - 1);
        return 1;
    }
        // debug(&term);
        //si on passe ici
        // ENTER a été pressé
    if (term->str_cmd[0] != '\0' && term->last_char == '\n')
        dprintf(1, "\n");
    term->ndx_cursor = 0;
    term->ndx_str = 0;
    term->ndx_line += 1;
	return 0;
}