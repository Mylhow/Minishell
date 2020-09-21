#ifndef ENV_H
# define ENV_H

#include "minishell.h"

typedef struct ENV
{
	char    *key;
	char    *value;
	void	*next;
} envir;

envir	*init_env(int ac, char **environnement, char **envp);
//      initialise l'environnement sous une forme de
//      liste chainé de structures ENV comportant chacun
//      une variable l'environnement sous le forme key/value
//      Return: renvoie NULL en cas d'erreur sinon un pointeur sur la liste chainée

int		parse_env_args(int ac, char **av, int *util_idx);
//      Fonction déterminant le mode de fonctionnement de env en fonction de ses parametres (voir env)

void    ft_env(int ac, char** argv, char **environnement);
//      fonction lancant un utilitaire dans un environnement modifié ou affichant l'environnement selon ses parametres.
//case 0: nothing
	//print env
//case 1: only variable
	//add variables
	//print env
// case 2: variables + utility
	//add variables
	//lunch utility
// case 3: only utility
	//lunch utility

// case 0: nothing
	//print env
// case 1: only with "="
	//add variables
	//print env
// case 2: One is without "="
	// add variables
	// lunch utility with the rest of the arguments

envir   *new_var(char *var);
//      fonction créant un nouveau maillon d'environnement(envir *) a partir d'un variable d'environnement(char *)

void	add_env_var(envir *env, char *var);
//      ajoute une nouvelle variable à la liste chainée d'environnment

envir   *dup_env(envir *env);
//      renvoie un pointeur sur une copie de la table d'environnemnet

void    del_env(envir *env);
//      supprime proprement la table d'environnement

void	print_env(envir *env);
//      affiche la table d'environnement

void	lunch_utility(char **argv, int i);
//      Fonction simulant le lancement d'un utilitaire

// EXPORT

int    export(int ac, char **argv, char **environnment);
//      Set an environment variable.

int check_var(char *variable);
//      check if the syntax of the env variable is correct
//      return 0 if the syntax is correct else return 1


#endif //ENV_H