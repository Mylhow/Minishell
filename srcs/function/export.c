#include "env.h"

int check_var(char *variable)
{
	int i;
	int equal_founded;


//peut commencer par un unique \
//ne peut commencer par un chiffre
//ne peut contenir de @ ou # ou . ou & avant le =

//apres le = peut contenir @ # 0-9 a-z A-Z . \ & ()

//Si pas de =, le nom est égal à NULL
	i = 0;
	equal_founded = 0;
	if (!variable)
		return -1;
	if (variable[i] == '\\')
		i++;
	if (variable[i] >= '0' && variable[i] <= '9')
		return -1;
	while (variable[i] != '\0' && equal_founded == 0)
	{
		if (variable[i] == '@' || variable[i] == '#' || variable[i] == '&' || variable[i] == '.')
			return -1;
		else if (variable[i] == '=')
			equal_founded = 1;
		i++;
	}
	if (equal_founded == 0)
		return 1;
	return 0;
}

int    export(int ac, char **argv, char **environnment)
{
	int i;
	int ret;
	envir *env;

	(void)ac;
	i = 1;
	ret = 0;
	env = (envir*)environnment;
	if (!argv || !*argv)
		return -1;
	while (env->next)
		env = env->next;
	while (argv[i])
	{
		// dprintf(1, "var = %s\n", argv[i]);
		ret = check_var(argv[i]);
		if ( ret < 0) //ici check validite de parametre
		{
			dprintf(1, "Syntax error.\n");
			return -1; 
		}
		add_env_var(env, argv[i]);
		i++;
	}
	if (i == 1)
		print_env((envir *)environnment);
	return 0;
}