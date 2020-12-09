#include "expander.h"

//TODO change this with some free-all function.
void  free_all(char **dst, char *simple_cmd)
{
    wrfree(dst);
    wrfree(simple_cmd);
}




/**  EXPAND_CMD
 *   description: expands a simple command into a command struct
 *   
 *   cmd: points to the destination of the expansion.
 *   simple_command: the simple command string that needs to be expanded.
 * 
 *   returns: 0 if everything has gone well, -1 if some expansion has failed.
 * 
 *   ORDER OF EXPANSION :
 *      - bash variables
 *      - word splitting
 *      - quote removal
 *      - backslash removal
 */

int     expand_cmd(t_cmd **cmd, char *simple_command)
{
    char **dst = 0;

    if (!(dst = wrmalloc(sizeof(char *))))
        return (-1);
    if (expand_var(dst, simple_command) != 0)
    {
        free_all(dst, NULL);
        return (-1);
    }
    simple_command = *dst;
    if (expand_word(cmd, *dst) != 0)
    {
        free_all(dst, simple_command);
        return (-1);
    }
    free_all(dst, simple_command);
    expand_quotes(*cmd);
    expand_bslash(*cmd);
    return (0);
}
