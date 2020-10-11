#include "terminal.h"

int ft_m_putchar(int c)
{
    write(1, (void *)&c, 1);
    return 1;
}

void    debug(t_term *term)
{
    int tmp;

    tmp = 3;
    tputs(term->caps.save, 1, ft_m_putchar);
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "last_char ='%c' code:%-20d\n", term->last_char, (int)term->last_char);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "ndx_cursor =%-20d\n", term->ndx_cursor);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "ndx_line =%-20d\n", term->ndx_line);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "ndx_str=%-20d\n", term->ndx_str);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "str_cmd = %-30s\n", term->str_cmd);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "str_cmd_size =%-20d\n", term->str_size);
    tmp ++;
    tputs(tgoto(term->caps.pos, 2 * term->caps.column / 4, tmp), 1, ft_m_putchar);
    dprintf(1, "str_cmd_alloc_size =%-20d\n", term->nb_blocks * STR_SIZE);

    tputs(term->caps.restore, 1, ft_m_putchar);
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