#include "terminal.h"
#include <stdio.h>
#include "libft.h"

static int     escape_sequences()
{
    t_term *term;

    term = (*getTerm());
    if (term->last_char == '\033') {
        term->esc_flag = 1;
        return (EXIT_FAILURE);
    }
    else if (term->esc_flag == 1 && term->last_char == '[')
    {
        term->esc_flag = 2;
        return (EXIT_FAILURE);
    }
    else if (term->esc_flag == 2)
    {
        if (term->last_char == LEFTCHAR)
            move_left();
        else if (term->last_char == RIGHTCHAR)
            move_right();
        else if (term->last_char == UPCHAR)
            move_up();
        else if (term->last_char == DOWNCHAR)
            move_down();
        term->esc_flag = 0;
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

static int     backspace()
{
    t_term *term;
    int i;

    term = (*getTerm());

    i = -1;
    if (term->ndx_str > 0)
    {
        term->ndx_str--;
        while (term->ndx_str + ++i <= term->str_size)
            term->str_cmd[term->ndx_str + i] = term->str_cmd[term->ndx_str + i + 1];
        term->ndx_cursor--;
        term->str_size--;
        term->str_cmd[term->ndx_str + i + 1] = '\0';
        put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
        put_caps(T_CLEOL, 0);
        dprintf(1, "%s", term->str_cmd + term->ndx_str);
        put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
    }
    // debug(term);
    return EXIT_SUCCESS;
}

void    insert()
{
    t_term *term;
    int i;

    i = 0;
    term = (*getTerm());
    while (term->str_size - i > term->ndx_str)
    {
        term->str_cmd[term->str_size - i] = term->str_cmd[term->str_size - 1 - i];
        i++;
    }
    term->str_cmd[term->ndx_str] = term->last_char;
    put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
    dprintf(1, "%s", term->str_cmd + term->ndx_str);
    term->ndx_cursor++;
    term->ndx_str++;
    term->str_size++;
}

static int     check_key()
{
    t_term  *term;
    int     line;

    term = (*getTerm());
    line = tigetnum(T_LINE);
    if (term->last_char == '\033' || term->esc_flag == 1 || term->esc_flag == 2)
        return (escape_sequences());
    if (term->last_char == 127 || term->last_char == 8)
        return (!backspace());
    if (term->last_char != '\n')
    {
        if (term->ndx_str == STR_SIZE * term->nb_blocks - 1)
        {
            term->str_cmd = realloc_str(term->str_cmd, (term->nb_blocks + 1) * STR_SIZE);
            term->nb_blocks++;
        }
        insert();
        return (EXIT_FAILURE);
    }
    return (EXIT_SUCCESS);
}

int     handle_key()
{
    t_term *term;

    term = (*getTerm());
    if (check_key())
        return (EXIT_FAILURE);
    if (term->str_cmd[0] != '\0' && term->last_char == '\n')
        dprintf(1, "\n");
    term->ndx_cursor = 0;
    term->ndx_str = 0;
    term->str_size = 0;
    term->ndx_line++;
    return (EXIT_SUCCESS);
}
