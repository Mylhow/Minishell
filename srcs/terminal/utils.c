#include "terminal.h"

int ft_m_putchar(int c)
{
    write(1, (void *)&c, 1);
    return 1;
}

void    debug(t_term *term)
{
    dprintf(1, "\nlast_char ='%c' code:%d\n", term->last_char, term->last_char);
    dprintf(1, "ndx_cursor =%d\n", term->ndx_cursor);
    dprintf(1, "ndx_str=%d\n", term->ndx_str);
    dprintf(1, "ndx_line =%d\n", term->ndx_line);
    dprintf(1, "str_cmd = %s\n", term->str_cmd);
    dprintf(1, "str_cmd_size =%d\n", term->nb_blocks * STR_SIZE);
}

char    *resize_str(char *str, int new_size)
{
    char    *tmp;
    int     i;

    i = 0;
    tmp = wrmalloc(new_size);
    ft_memset(tmp, '\0', new_size);
    while (str[i] != '\0')
    {
        tmp[i] = str[i];
        i++;
    }
    wrfree(str);
    return tmp;
}