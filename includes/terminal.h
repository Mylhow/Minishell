#ifndef TERMINAL_H
# define TERMINAL_H

# define T_CLEAR "clear"
# define T_CLEOL "el"
# define T_FCOLOR "setaf"
# define T_BCOLOR "setab"
# define T_BLINK "blink"
# define T_BOLD "bold"
# define T_UNDER "smul"
# define T_RESET "sgr0"
# define T_POS "cup"
# define T_SAVE "sc"
# define T_RESTORE "rc"
# define T_UP "cuu1"
# define T_DOWN "cud1"
# define T_RIGHT "cuf1"
# define T_LEFT "cub1"
# define T_COLUMN "cols"
# define T_LINE "lines"

# define STR_SIZE 64

typedef struct 		termios	t_termios;

typedef struct		s_term
{
	int 			nb_blocks;
	int				ndx_cursor;
	int				ndx_line;
	int 			ndx_str;
	int				str_size;
	unsigned char	last_char;
	char 			*str_cmd;
	char 			esc_flag;
	t_termios 		termios;
	t_termios		termios_backup;
}					t_term;

t_term **getTerm(void);
int init_term();
int put_caps(char *caps, int color);
int put_cursor(int col, int row);
#endif