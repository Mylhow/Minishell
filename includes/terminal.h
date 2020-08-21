#ifndef TERM_H
 #define TERM_H
    #include "libft_string.h"
    #include "libft_put.h"
    #include "libft_mem.h"
    #include <curses.h>
    #include <term.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    #define STR_SIZE 64
    #define PROMPT_SIZE 1
    // dprintf(1, "\033[6n"); //affiche la position du curseur

    typedef struct termios t_termios;
    typedef struct  s_caps
    {
        char *clear;
        char *cl_eol;
        char *fcolor;
        char *bcolor;
        char *blink;
        char *reset;
        char *bold;
        char *under;
        char *pos;
        char *up;
        char *down;
        char *right;
        char *left;
        int column;
        int line;
    }               t_caps;
    typedef struct  s_term
    {
        int         nb_blocks; //nb_block * STR_SIZE = taille alloué pour la commande
        int         ndx_cursor; //indice du curseur sur une ligne
        int         ndx_line; //indique la ligne du curseur
        int         ndx_str; //indice du curseur sur la str_cmd
        char        last_char; //dernier caractere tapé
        char        *str_cmd; //commande
        char        esc_flag;
        t_caps      caps;
        t_termios   termios;
        t_termios   termios_backup;
    }               t_term;

    //init_term.c
    int     init_term(t_term *term);
    int     config_term(t_term *term);
    //handle_key.c
    int		handle_key(t_term *term);
    // utils.c
    void    debug(t_term *term);
    int     ft_m_putchar(int c);
    char    *resize_str(char *str, int new_size);


#endif //TERM_H