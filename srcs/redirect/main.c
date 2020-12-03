#include "exec.h"

#include <stdio.h>
int 			main(int ac, char **av, char **envp)
{
    (void)ac;
    (void)av;
	char cmd[] =
    //"$ECHO \\$HOME $NULL$NULL$HOME$HOME$FILE 0 $= $FILE '$FILE' \"$FILE\" '\"$FILE\"' \"'$FILE'\" \"\\\"$FILE\" \\\\ aaa\"b  c\" 'hello'aaa \"a   b\"b \'a\'\'b\' $HOME$FILE$HOME $HOME$NULL$HOME a>file > test1 test2 >> $FILE >file4>\"file5<file6\"";
	"ca -e redirect.c > file1";
    backup_io(); // call this once for all execution
    exec_str(cmd, envp);
	return (0);
}
