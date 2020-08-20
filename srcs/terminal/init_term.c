#include "terminal.h"

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

void    init_caps(t_caps *caps)
{
    caps->clear = tigetstr("clear");
    caps->fcolor = tigetstr("setaf");
    caps->reset = tigetstr("sgr0");
    caps->under = tigetstr("smul");
    caps->bold = tigetstr("bold");
    caps->blink = tigetstr("blink");
    caps->pos = tigetstr("cup");
    caps->column = tigetnum("cols");
    caps->line = tigetnum("lines");
}
int config_term(t_term *term)
{
    if (tigetflag("os") != 0)
    {
        printf("os error\n");
        return -1;
    }
    if (tcgetattr(0, &term->termios) == -1)
        return (-1);
    if (tcgetattr(0, &term->termios_backup) == -1)
        return (-1);
    term->termios.c_lflag &= ~(ICANON); /* Met le terminal en mode non canonique. La fonction read recevra les entrées clavier en direct sans attendre qu'on appuie sur Enter */
    term->termios.c_lflag &= ~(ECHO); /* Les touches tapées au clavier ne s'affficheront plus dans le terminal */
    if (tcsetattr(0, 0, &term->termios) == -1)
        return (-1);
    return 0;
}
void    print_start(t_term *term)
{
    tputs(tgoto(term->caps.pos, 13, term->caps.line), 1, putchar);
    tputs(term->caps.clear, 1, putchar);
    tputs(term->caps.blink, 1, putchar);
    tputs(term->caps.bold, 1, putchar);
    tputs(tparm(term->caps.fcolor, COLOR_YELLOW), 1, putchar);
    printf("------___-----------------------___-----------------------___-----------___-----------___--------------------------------\n     /__/\\        ___          /__/\\        ___          /  /\\         /__/\\         /  /\\ \n    |  |::\\      /  /\\         \\  \\:\\      /  /\\        /  /:/_        \\  \\:\\       /  /:/_                               \n    |  |:|:\\    /  /:/          \\  \\:\\    /  /:/       /  /:/ /\\        \\__\\:\\     /  /:/ /\\    ___     ___   ___     ___ \n  __|__|:|\\:\\  /__/::\\      _____\\__\\:\\  /__/::\\      /  /:/ /::\\   ___ /  /::\\   /  /:/ /:/_  /__/\\   /  /\\ /__/\\   /  /\\\n /__/::::| \\:\\ \\__\\/\\:\\__  /__/::::::::\\ \\__\\/\\:\\__  /__/:/ /:/\\:\\ /__/\\  /:/\\:\\ /__/:/ /:/ /\\ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/\n \\  \\:\\~~\\__\\/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/    \\  \\:\\/\\ \\  \\:\\/:/~/:/ \\  \\:\\/:/__\\/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/   \\  \\:\\  /:/ \n  \\  \\:\\           \\__\\::/  \\  \\:\\  ~~~      \\__\\::/  \\  \\::/ /:/   \\  \\::/       \\  \\::/ /:/    \\  \\:\\/:/     \\  \\:\\/:/  \n   \\  \\:\\          /__/:/    \\  \\:\\          /__/:/    \\__\\/ /:/     \\  \\:\\        \\  \\:\\/:/      \\  \\::/       \\  \\::/   \n    \\  \\:\\         \\__\\/      \\  \\:\\         \\__\\/       /__/:/       \\  \\:\\        \\  \\::/        \\__\\/         \\__\\/    \n");
    tputs(term->caps.under, 1, putchar);
    printf("\\----\\__\\/---------------------\\__\\/---------------------\\__\\/---------\\__\\/---------\\__\\/-------------------------------/\n");
    tputs(term->caps.reset, 1, putchar);
    tputs(tparm(term->caps.fcolor, COLOR_CYAN), 1, putchar);
    printf("\t~By Nlecaill, Dgascon et Lrobino\n\n");
    term->ndx_line += 13;
}
int init_term_variables(t_term *term)
{
    term->nb_blocks = 1;
    term->ndx_cursor = 0;
    term->ndx_line = 0;
    term->last_char = '\0';
    term->str_cmd = (char *)wrmalloc(STR_SIZE * term->nb_blocks);
    ft_memset(term->str_cmd, '\0', STR_SIZE);
    return 0;
}
// TODO selon la taille du terminal, spliter "MINISHELL"
int init_term(t_term *term)
{
    if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
        return (-1);
    init_caps(&term->caps);
    init_term_variables(term);
    // printf("TERM size: %d %d\n", column_count, line_count);
    if (tigetflag("os") != 0)
        printf("os error\n");
    // print_escape_sequence(reset_cmd);
    print_start(term);
    tputs(term->caps.reset, 1, putchar);
    return 0;
}