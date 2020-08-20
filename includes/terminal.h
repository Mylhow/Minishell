#ifndef TERM_H
 #define TERM_H
    #include "minishell.h"
    #include <curses.h>
    #include <term.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
    

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
    int init_term(void);

#endif //TERM_H