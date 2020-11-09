#include "expander.h"

#include <stdio.h>
int 			main()
{
	char cmd[] =
 "echo $ $= $@@@ $_ $- $FILE '$FILE' \"$FILE\" '\"$FILE\"' \"'$FILE'\" \"\\\"$FILE\"";
	char *expanded = 0;
	expand_str(&expanded, cmd);
	if (expanded)
		printf ("$FILE=file\ncmd: %s\nexp: %s\n", cmd, expanded);
	free(expanded);
	return (0);
}
