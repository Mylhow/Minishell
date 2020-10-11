#include "terminal.h"

void    init_caps(t_caps *caps)
{
    caps->clear = tigetstr("clear");
    caps->cl_eol = tigetstr("el");
    caps->fcolor = tigetstr("setaf");
    caps->bcolor = tigetstr("setab");
    caps->reset = tigetstr("sgr0");
    caps->under = tigetstr("smul");
    caps->bold = tigetstr("bold");
    caps->blink = tigetstr("blink");
    caps->pos = tigetstr("cup");
    caps->column = tigetnum("cols");
    caps->line = tigetnum("lines");
    caps->up = tigetstr("cuu1");
    caps->down = tigetstr("cud1");
    caps->right = tigetstr("cuf1");
    caps->left = tigetstr("cub1");
    caps->save = tigetstr("sc");
    caps->restore = tigetstr("rc");
}
//configure le terminal de facon canonique et de couper la liaison entre le terminal et le clavier 
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
static void    print_start(t_term *term)
{
    // tputs(tgoto(term->caps.pos, 13, term->caps.line), 1, ft_m_putchar);
    tputs(term->caps.clear, 1, ft_m_putchar);
    tputs(term->caps.blink, 1, ft_m_putchar);
    tputs(term->caps.bold, 1, ft_m_putchar);
    tputs(tparm(term->caps.fcolor, COLOR_YELLOW), 1, ft_m_putchar);
    if (term->caps.column > 121)
    {
        printf("------___-----------------------___-----------------------___-----------___-----------___--------------------------------\n     /__/\\        ___          /__/\\        ___          /  /\\         /__/\\         /  /\\ \n    |  |::\\      /  /\\         \\  \\:\\      /  /\\        /  /:/_        \\  \\:\\       /  /:/_                               \n    |  |:|:\\    /  /:/          \\  \\:\\    /  /:/       /  /:/ /\\        \\__\\:\\     /  /:/ /\\    ___     ___   ___     ___ \n  __|__|:|\\:\\  /__/::\\      _____\\__\\:\\  /__/::\\      /  /:/ /::\\   ___ /  /::\\   /  /:/ /:/_  /__/\\   /  /\\ /__/\\   /  /\\\n /__/::::| \\:\\ \\__\\/\\:\\__  /__/::::::::\\ \\__\\/\\:\\__  /__/:/ /:/\\:\\ /__/\\  /:/\\:\\ /__/:/ /:/ /\\ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/\n \\  \\:\\~~\\__\\/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/    \\  \\:\\/\\ \\  \\:\\/:/~/:/ \\  \\:\\/:/__\\/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/   \\  \\:\\  /:/ \n  \\  \\:\\           \\__\\::/  \\  \\:\\  ~~~      \\__\\::/  \\  \\::/ /:/   \\  \\::/       \\  \\::/ /:/    \\  \\:\\/:/     \\  \\:\\/:/  \n   \\  \\:\\          /__/:/    \\  \\:\\          /__/:/    \\__\\/ /:/     \\  \\:\\        \\  \\:\\/:/      \\  \\::/       \\  \\::/   \n    \\  \\:\\         \\__\\/      \\  \\:\\         \\__\\/       /__/:/       \\  \\:\\        \\  \\::/        \\__\\/         \\__\\/    \n");
        tputs(term->caps.under, 1, ft_m_putchar);
        printf("\\----\\__\\/---------------------\\__\\/---------------------\\__\\/---------\\__\\/---------\\__\\/-------------------------------/\n");
        term->ndx_line += 13;
    }
    else
    {
        printf("      ___                       ___\n");
        printf("     /__/\\        ___          /__/\\        ___\n");
        printf("    |  |::\\      /  /\\         \\  \\:\\      /  /\\\n");
        printf("    |  |:|:\\    /  /:/          \\  \\:\\    /  /:/\n");
        printf("  __|__|:|\\:\\  /__/::\\      _____\\__\\:\\  /__/::\\\n");
        printf(" /__/::::| \\:\\ \\__\\/\\:\\__  /__/::::::::\\ \\__\\/\\:\\__\n");
        printf(" \\  \\:\\~~\\__\\/    \\  \\:\\/\\ \\  \\:\\~~\\~~\\/    \\  \\:\\/\\\n");
        printf("  \\  \\:\\           \\__\\::/  \\  \\:\\  ~~~      \\__\\::/\n");
        printf("   \\  \\:\\          /__/:/    \\  \\:\\          /__/:/\n");
        printf("    \\  \\:\\         \\__\\/      \\  \\:\\         \\__\\/\n");
        tputs(term->caps.under, 1, ft_m_putchar);
        printf("-----\\__\\/---------------------\\__\\/-----------------\n");
        tputs(term->caps.reset, 1, ft_m_putchar);
        tputs(term->caps.blink, 1, ft_m_putchar);
        tputs(term->caps.bold, 1, ft_m_putchar);
        tputs(tparm(term->caps.fcolor, COLOR_YELLOW), 1, ft_m_putchar);
        printf("\t         ___           ___           ___                                    \n");
        printf("\t        /  /\\         /__/\\         /  /\\                                   \n");
        printf("\t       /  /:/_        \\  \\:\\       /  /:/_                                  \n");
        printf("\t      /  /:/ /\\        \\__\\:\\     /  /:/ /\\    ___     ___   ___     ___    \n");
        printf("\t     /  /:/ /::\\   ___ /  /::\\   /  /:/ /:/_  /__/\\   /  /\\ /__/\\   /  /\\   \n");
        printf("\t    /__/:/ /:/\\:\\ /__/\\  /:/\\:\\ /__/:/ /:/ /\\ \\  \\:\\ /  /:/ \\  \\:\\ /  /:/   \n");
        printf("\t    \\  \\:\\/:/~/:/ \\  \\:\\/:/__\\/ \\  \\:\\/:/ /:/  \\  \\:\\  /:/   \\  \\:\\  /:/    \n");
        printf("\t     \\  \\::/ /:/   \\  \\::/       \\  \\::/ /:/    \\  \\:\\/:/     \\  \\:\\/:/     \n");
        printf("\t      \\__\\/ /:/     \\  \\:\\        \\  \\:\\/:/      \\  \\::/       \\  \\::/      \n");
        printf("\t        /__/:/       \\  \\:\\        \\  \\::/        \\__\\/         \\__\\/       \n");
        tputs(term->caps.under, 1, ft_m_putchar);
        printf("\t--------\\__\\/---------\\__\\/---------\\__\\/--------------------------------   \n");
    term->ndx_line += 24;
    }
    
    tputs(term->caps.reset, 1, ft_m_putchar);
    tputs(tparm(term->caps.fcolor, COLOR_CYAN), 1, ft_m_putchar);
    printf("\t~By Nlecaill, Dgascon, Abourbou et Lrobino\n\n");
}
int init_term_variables(t_term *term)
{
    term->nb_blocks = 1;
    term->ndx_cursor = 0;
    term->ndx_line = 0;
    term->ndx_str = 0;
    term->last_char = '\0';
    term->esc_flag = 0;
    term->str_cmd = (char *)wrmalloc(STR_SIZE * term->nb_blocks);
    ft_memset(term->str_cmd, '\0', STR_SIZE);
    return 0;
}
int init_term(t_term *term)
{
    if (setupterm(NULL, STDOUT_FILENO, NULL) != 0)
        return (-1);
    init_caps(&term->caps);
    init_term_variables(term);
    if (tigetflag("os") != 0)
        printf("os error\n");
    print_start(term);
    tputs(term->caps.reset, 1, putchar);
    return 0;
}