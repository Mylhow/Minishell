#include "terminal.h"

int ft_m_putchar(int c)
{
    write(1, (void *)&c, 1);
    return 1;
}

void    debug(t_term *term)
{
    dprintf(1, "\nlast_char =%c\n", term->last_char);
    dprintf(1, "ndx_cursor =%d\n", term->ndx_cursor);
    dprintf(1, "ndx_line =%d\n", term->ndx_line);
    dprintf(1, "str_cmd = %s\n", term->str_cmd);
}
