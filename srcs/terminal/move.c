#include "terminal.h"

void     move_right()
{
    t_term *term;

    term = (*getTerm());
    if (term->ndx_str < term->str_size)
    {
        if (term->ndx_cursor < tigetnum(T_COLUMN))
        {
            term->ndx_cursor++;
            put_caps(T_RIGHT, 0);
        }
        else
        {
            term->ndx_cursor = 0;
            term->ndx_line += 1;
            put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
        }
        term->ndx_str++;
    }
}

void     move_left()
{
    t_term *term;

    term = (*getTerm());
    if (term->ndx_str > 0)
    {
        if (term->ndx_cursor > 0)
        {
            term->ndx_cursor--;
            put_caps(T_LEFT, 0);
        }
        else
        {
            term->ndx_cursor = tigetnum(T_COLUMN);
            term->ndx_line -= 1;
            put_cursor(term->ndx_cursor + PROMPT_SIZE, term->ndx_line);
        }
        term->ndx_str--;
    }
}

void     move_up()
{
    t_term *term;

    term = (*getTerm());
    if (term->ndx_str / tigetnum(T_COLUMN) > 1)
    {
        term->ndx_str -= tigetnum(T_COLUMN);
        term->ndx_line -= 1;
        put_caps(T_UP, 0);
    }
}

void     move_down()
{
    t_term *term;

    term = (*getTerm());
    if (term->ndx_str / tigetnum(T_COLUMN) < term->str_size / tigetnum(T_COLUMN))
        put_caps(T_DOWN, 0);
}
