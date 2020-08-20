#ifndef TERM_H
 #define TERM_H
    #include "minishell.h"
    #include "libft_string.h"
    #include "libft_put.h"
    #include "libft_mem.h"
    #include <curses.h>
    #include <term.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    #define STR_SIZE 64
    // dprintf(1, "\033[6n"); //affiche la position du curseur

    typedef struct termios t_termios;
    typedef struct  s_caps
    {
        char *clear;
        char *fcolor;
        char *blink;
        char *reset;
        char *bold;
        char *under;
        char *pos;
        int column;
        int line;
    }               t_caps;
    typedef struct  s_term
    {
        int         nb_blocks;
        int         ndx_cursor;
        int         ndx_line;
        char        last_char;
        char        *str_cmd;
        t_caps      caps;
        t_termios   termios;
        t_termios   termios_backup;
    }               t_term;

    int     init_term(t_term *term);
    int     config_term(t_term *term);
    int     ft_m_putchar(int c);
    char    *resize_str(char *str, int new_size);


#endif //TERM_H