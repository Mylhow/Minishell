#include "expander.h"

//TODO change this with some free-all function.
void  free_all(char **dst, char *simple_cmd)
{
    free(dst);
    free(simple_cmd);
}




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
    if (expand_var(dst, simple_command) != 0)
    {
        free_all(dst, NULL);
        return (-1);
    }
	printf ("- Expanded vars\n");
    simple_command = *dst;
    if (expand_word(cmd, *dst) != 0)
    {
        free_all(dst, simple_command);
        return (-1);
    }
    printf ("- Expanded words\n");
    free_all(dst, simple_command);
    expand_quotes(*cmd);
    printf ("- Expanded quotes\n");
    expand_bslash(*cmd);
    printf ("- Expanded backslash\n");
    return (0);
}
