#include "env.h"
#include "libft_printf.h"
#include "libft_string.h"

// Okay.. Alors tu dois déjà fork() pour lancer la commande depuis un autre process, exécuter la commande avec execve(path, argv, env) dans le fork puis wait que le process soit terminé,
// En gros :

// If (pid = fork())
// {
//     execve(...)
// }
// else
// wait(pid, status, opt)
// Oh et excuse utilise waitpid() pas wait

// Le pid est de type pid_t et tu dois inclure unistd sys/wait sys/types

// errno et perror
// env: lancer une commande apres avoir modifié les variables d'environnment
// 		env print only variable with value
// export: crée ou supprimer une variable d'environnment
//		export can set variable without value


// int		parse_env_args(int ac, char **av, int *util_idx)
// {
// 	// Si "=" alors variable
// 	// Si pas de "=" alors test si built-in
// 	// Si oui, alors la suite n'est qu'argument de ce built-in
// 	// Sinon renvoi une erreur
// 	int		arg;
// 	int		i;
// 	int		equel_found;

// 	i = 0;
// 	arg = 0;
// 	equel_found = 0;
// 	if (ac == 0)
// 		return 0;
// 	while (av[arg])
// 	{
// 		while (av[arg][i])
// 		{
// 			if (av[arg][i] == '=')
// 				equel_found = 1;
// 			i++;
// 		}
// 		if (equel_found == 0)
// 		{
// 			*util_idx = arg;
// 			if (arg == 0)
// 				return 3;
// 			else
// 				return 2;
// 		}
// 		equel_found = 0;
// 		i = 0;
// 		arg++;
// 	}
// 	return 1;
// }

int		parse_export(int ac, char **argv)
{
	int i;

	i = 0;
	//check var
	while (i < ac)
	{
		ft_printf("my arg = %s\n", argv[i]);
		i++;
	}
	//check command
	ft_printf("my command = %s\n", argv[i]);
	return 0;
}

void	lunch_utility(char **argv, int i)
{
	ft_printf("LUNCH the utility: %15s with params:\n", argv[i]);
	i++;
	while (argv[i])
	{
		ft_printf("\t%s\n", argv[i]);
		i++;
	}
}

int is_utility(char *var)
{
	if(ft_strcmp(var, "echo") == 0)
		return 1;
	return 0;
}

//A sécuriser
//Fonctions de suppression de l'environnement à faire
// penser a checker les variables de ft_env aussi (faire une fonction variable_syntax() a utiliser dans ft_env et dans export)
void	ft_env(int ac, char** argv, char **environnement)
{
	envir	*env;
	int 	i;
	int		x;
	int		equal_found;

	if (ac < 0) // A mettre a jour avec les bonnes valeurs
		return;
	i = 0;
	x = 0;
	equal_found = 0;
	env = dup_env((envir *)environnement);	
	while (argv != NULL && argv[i] != NULL)
	{
		while (argv[i][x])
		{
			if (argv[i][x] == '=')
				equal_found = 1;
			x++;
		}
		if (equal_found == 0)
		{
			if (is_utility(argv[i]) == 1)
				lunch_utility(argv, i);
			else
				ft_printf("variable syntax error\n");
			return ;
		}
		add_env_var(env, argv[i]);
		equal_found = 0;
		x = 0;
		i++;
	}
	print_env(env);
	return;
}




// void    ft_env(int ac, char** argv, char **environnement)
// {
// 	envir	*env;
// 	int		cas;
// 	int 	i;
// 	int		util_idx;

// 	if ((!argv || !*argv) && ac != 0)
// 		return;	
// 	i = 0;
// 	util_idx = 0;
// 	cas = parse_env_args(ac, argv, &util_idx);
// 	env = dup_env((envir *)environnement);
// 	ft_printf("CASE = %d\n", cas);
// 	if (cas == 0)
// 		print_env(env);
// 	else if (cas == 1)
// 	{
// 		while (i < ac)
// 		{
// 			add_env_var(env, argv[i]);
// 			i++;
// 		}
// 		print_env(env);
// 	}
// 	else if (cas == 2)
// 	{
// 		while (i < util_idx)
// 		{
// 			add_env_var(env, argv[i]);
// 			i++;
// 		}
// 		lunch_utility(argv, i);
// 	}
// 	else
// 		lunch_utility(argv, i);
// }

// // check la syntax de la nouvelle variable d'environnment
// // retourne 1 si une erreur de syntax est presente, sinon 0


envir	*init_env(int ac, char **environnement, char **envp)
{
	int env_index;
	envir *before;
	envir *env;
	envir *first;

	(void)ac;
	(void)environnement;
	env_index = 0;
	//init premier maillon
	if (envp[env_index])
	{
		if (!(first = new_var(envp[env_index])))
		{
			ft_printf("break1");
			return(NULL);
		}
		env = first;
		before = env;
		env_index++;
	}
	//init toute la chaine
	while (envp[env_index])
	{
		if (!(env = new_var(envp[env_index])))
		{
			ft_printf("break");
			return(NULL);
		}
		before->next = env;
		before = env;
		env_index++;
	}
	return first;
}