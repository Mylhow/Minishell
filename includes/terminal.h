#ifndef TERMINAL_H
# define TERMINAL_H

# include <term.h>
# include "libft_hash.h"

# define T_CLEAR "clear"
# define T_CLEOL "el"
# define T_FCOLOR "setaf"
# define T_BCOLOR "setab"
# define T_RESET "sgr0"
# define T_POS "cup"
# define T_COLUMN "cols"
# define T_LINE "lines"

# define PROMPT_SIZE 2

# define LEFTCHAR 'D'
# define RIGHTCHAR 'C'
# define UPCHAR 'A'
# define DOWNCHAR 'B'
# define DELCHAR 127
# define BACKSPACE 8
# define ENDCHAR 'F'
# define HOMECHAR 'H'
# define _EOF 4

# define PROCESS_SUCCESS 2

typedef struct termios	t_termios;

/*
 ** Structure d un bloc. Bloc = une commande
*/

typedef struct			s_block
{
	int					nb_blocks;
	int					size;
	int					alloc_size;
	char				*str_cmd;
}						t_block;

/*
 ** Structure du temrinal. (ESC char 1. [ char 2. CTRL char 3)
*/

typedef struct			s_term
{
	t_hash				*list_blocks;
	t_hash				*historic;
	t_hash				*current_historic;
	t_hash				*current_block;
	char				*str_ccmd;
	int					cursor_pos;
	int					addposcurs;
	int					ndx_cursor;
	int					ndx_line;
	int					original_line;
	unsigned char		last_char;
	int					esc_flag;
	int					nb_cols;
	int					nb_lines;
	t_termios			termios;
	t_termios			termios_backup;
}						t_term;

t_term					**getterm(void);

void					get_pos(void);
int						put_caps(char *caps, int color);
int						put_cursor(int col, int row);
int						clear_eos(t_term *term, int original_line);

int						init_term(void);

char					*ft_strjoinblock(t_hash *hash);
t_block					*ft_blockdup(t_block *block);
t_block					*ft_blockhashdup(t_hash *hash);
t_block					*ft_blocknew(void);
t_block					*ft_blockstrnew(char *s);

int						ft_newline(t_term *term);
int						new_cmd(t_term *term, int sig, int ret_handle);

int						handle_key(void);
int						insert(t_term *term, t_block *block);
int						escape_sequences(t_term *term, t_block *block);
int						backspace(t_term *term, t_block *block);

int						move_manage(t_term *term, t_block *block);
void					move_right(t_block *block);
void					move_left(void);
int						move_up(t_term *term);
int						move_down(t_term *term);

int						ctrl_manage(t_term *term, t_block *block, char my_char);
void					ctrl_up(t_term *term);
void					ctrl_down(t_term *term, t_block *block);
void					ctrl_left(t_term *term, t_block *block);
void					ctrl_right(t_term *term, t_block *block);

int						ft_histo_add(t_term *term, char *key, void *value);
int						print_historic(t_term *term, t_block *dup);

char					*realloc_str(char *str, int new_size);
void					debug(t_term *term);
#endif
