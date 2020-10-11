#ifndef TERM_H
 #define TERM_H
    #include "libft_string.h"
    #include "libft_put.h"
    #include "libft_mem.h"
    #include "libft_number.h"
    
    #include <term.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    #define STR_SIZE 64
    #define PROMPT_SIZE 2
    
    //tparm colors
    #define COLOR_BLACK	0
    #define COLOR_RED	1
    #define COLOR_GREEN	2
    #define COLOR_YELLOW	3
    #define COLOR_BLUE	4
    #define COLOR_MAGENTA	5
    #define COLOR_CYAN	6
    #define COLOR_WHITE	7
    // dprintf(1, "\033[6n"); //affiche la position du curseur

    typedef struct termios t_termios;
    typedef struct  s_caps
    {
        char *clear;
        char *cl_eol;

        char *fcolor;
        char *bcolor;
        char *blink;
        char *bold;
        char *under;
        char *reset;

        char *pos;
        char *save;
        char *restore;
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
        int         ndx_str; //indice du curseur sur la str_cmd``
        int         str_size; //taille de la commande tapé (en octets)
        unsigned char        last_char; //dernier caractere tapé
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