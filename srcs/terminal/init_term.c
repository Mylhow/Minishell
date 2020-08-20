#include "term.h"
#include <curses.h>
#include <terminal.h>

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

// TODO selon la taille du terminal, spliter "MINISHELL"
int init_term(void)
{
    t_caps  caps;

    if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
        return (-1);
    init_caps(&caps);

    // printf("TERM size: %d %d\n", column_count, line_count);
    if (tigetflag("os") != 0)
        printf("os error\n");
    // print_escape_sequence(reset_cmd);
    tputs(tgoto(caps.pos, 13, caps.line), 1, putchar);
    tputs(caps.clear, 1, putchar);
    tputs(caps.blink, 1, putchar);
    tputs(caps.bold, 1, putchar);
    tputs(tparm(caps.fcolor, COLOR_YELLOW), 1, putchar);
    printf("------___-----------------------___-----------------------___-----------___-----------___--------------------------------\n     /__/\\        ___          /__/\\        ___          /  /\\         /__/\\         /  /\\ \n    |  |::\\      /  /\\         \\  \\:\\      /  /\\        /  /:/_        \\  \\:\\       /  /:/_                               \n    |  |:|:\\    /  /:/          \\  \\:\\    /  /:/       /  /:/ /\\        \\__\\:\\     /  /:/ /\\    ___     ___   ___     ___ \n  __|__|:|\\:\\  /__/::\\      _____\\__\\:\\  /__/::\\      /  /:/ /::\\   ___ /  /::\\   /  /:/ /:/_  /__/\\   /  /\\ /__/\\   /  /\\\n /__/::::| \\:\\ \\__\\/\\:\\__  /__/::::::::\\ \\__\\/\\:\\__  /__/:/ /:/\\:\\ /__/\\  /:/\\:\\ /__/:/ /:/ /\\ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/\n \\  \\:\\~~\\__\\/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/    \\  \\:\\/\\ \\  \\:\\/:/~/:/ \\  \\:\\/:/__\\/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/   \\  \\:\\  /:/ \n  \\  \\:\\           \\__\\::/  \\  \\:\\  ~~~      \\__\\::/  \\  \\::/ /:/   \\  \\::/       \\  \\::/ /:/    \\  \\:\\/:/     \\  \\:\\/:/  \n   \\  \\:\\          /__/:/    \\  \\:\\          /__/:/    \\__\\/ /:/     \\  \\:\\        \\  \\:\\/:/      \\  \\::/       \\  \\::/   \n    \\  \\:\\         \\__\\/      \\  \\:\\         \\__\\/       /__/:/       \\  \\:\\        \\  \\::/        \\__\\/         \\__\\/    \n");
    tputs(caps.under, 1, putchar);
    printf("\\----\\__\\/---------------------\\__\\/---------------------\\__\\/---------\\__\\/---------\\__\\/-------------------------------/\n");
    tputs(caps.reset, 1, putchar);
    tputs(tparm(caps.fcolor, COLOR_CYAN), 1, putchar);
    printf("\t~By Nlecaill, Dgascon et Lrobino\n\n");
    tputs(caps.reset, 1, putchar);
    return 0;
}