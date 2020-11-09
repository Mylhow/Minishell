#include "expander.h"

int     expand_str(char **dst, char *simple_command)
{
    char    *output;

    if (expand_var(&output, simple_command))
        return (-1);
    *dst = output;
    return (0);
}