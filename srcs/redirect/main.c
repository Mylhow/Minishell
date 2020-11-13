#include "exec.h"

#include <stdio.h>
int 			main()
{
	char cmd[] =
    "$ECHO \\$HOME $NULL$NULL$HOME$HOME$FILE 0 $= $FILE '$FILE' \"$FILE\" '\"$FILE\"' \"'$FILE'\" \"\\\"$FILE\" \\\\ aaa\"b  c\" 'hello'aaa \"a   b\"b \'a\'\'b\' $HOME$FILE$HOME $HOME$NULL$HOME a>file > test1 test2 >> $FILE >file4>\"file5<file6\"";
	t_cmd *expanded = 0;

	expand_cmd(&expanded, cmd);
    parse_redirections(expanded);
    //handle_redirection(expanded->l_redir);
	if (expanded)
    {
		printf ("\n$FILE=\"f1  f2\"\n\n\033[1;35mTEST\033[0m: -> %s\n\n\033[1;35mLIST\033[0m: -> ", cmd);
        while (expanded->l_argv)
        {
            if (expanded->l_argv->content)
                printf ("[%s] ", (char *)expanded->l_argv->content);
            expanded->l_argv = expanded->l_argv->next;
        }
        printf ("\n\n\033[1;35mREDIRECT\033[0m: -> ");
        while (expanded->l_redir)
        {
            if (expanded->l_redir->content)
            {
                t_redirect  *red = (t_redirect *)expanded->l_redir->content;
                printf ("redirection: [%s] [%s]    ", red->type, red->file);
            }
            expanded->l_redir = expanded->l_redir->next;
        }
    }
    printf ("\n");
   // printf ("\n\033[1;35mREAL\033[0m: -> echo ");
    fflush(stdout);
    //system(cmd);
	free(expanded);
	return (0);
}
