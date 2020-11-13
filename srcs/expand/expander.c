#include "expander.h"

/** ORDER:
 *  - bash variables
 *  - word splitting
 *  - quote removal
 *  - backslash removal
 */

int     expand_cmd(t_cmd **cmd, char *simple_command)
{
    char **dst = 0;

    if (!(dst = malloc(sizeof(char *))))
        return (-1);
    if (expand_var(dst, simple_command))
        return (-1);
    simple_command = *dst;
    if (expand_word(cmd, *dst))
        return (-1);
    free(dst);
    free(simple_command);
    expand_quotes(*cmd);
    expand_bslash(*cmd);
    return (0);
}
