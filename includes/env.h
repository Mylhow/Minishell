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
//      Return: renvoie -1 en cas d'erreur sinon 0

int		parse_env_args(int ac, char **av, int *util_idx);
//      Fonction déterminant le mode de fonctionnement de env en fonction de ses parametres (voir env)

void    env(int ac, char** argv, char **environnement);
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


#endif //ENV_H