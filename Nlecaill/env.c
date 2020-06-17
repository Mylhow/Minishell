#include "libft.h"

# define ENVTAB_SIZE 100

typedef struct ENV
{
    char    *tab;
    int     tab_size;
} envir;

void    env(envir* env)
{
    ft_printf("%s", env->tab);
}

//check la syntax de la nouvelle variable d'environnment
int check_var(char *variable)
{
    int i;
    int find_equal;

//peut commencer par un unique \
//ne peut commencer par un chiffre
//ne peut contenir de @ ou # ou . avant le =

//apres le = peut contenir @ # 0-9 a-z A-Z . 
    i = 0;
    find_equal = 0;
    if (!variable)
        return -1;
    if (variable[i] == '\\')
        i++;
    if (variable[i] >= '0' && variable[i] <= '9')
        return 1;
    while (variable[i] != '\0' && find_equal == 0)
    {
        if (variable[i] == '@' || variable[i] == '#')
            return 1;
        else if (variable[i] == '=')
            find_equal = 1;
        i++;
    }
    if (!find_equal)
        return 1;
    return 0;
}

int    export(envir *env, char *variable)
{
    int var_size;
    int env_size;
    char *new;

    if (check_var(variable) != 0)
        return -1;
    env_size = ft_strlen(env->tab);
    var_size = ft_strlen(variable);

    //réadapte la taille de env->tabsize si necessaire
    while (env_size + var_size >= env->tab_size - 1 && env->tab_size < 2000)
    {
        env->tab_size += ENVTAB_SIZE;
        new = (char*)malloc(env->tab_size * sizeof(char));
        ft_strlcpy(new, env->tab, env_size + 1);
        //remplie de 0 la fin
        while (env_size < env->tab_size)
        {
            new[env_size] = '\0';
            env_size++;
        }
        free(env->tab);
        env->tab = new;
        env_size = ft_strlen(env->tab);
    }
    var_size = 0;
    while(variable[var_size])
    {
        env->tab[env_size] = variable[var_size];
        env_size++;
        var_size++;
    }
    env->tab[env_size] = '\n';
    return 0;
}

int copy_env(envir *env, char **envp)
{
    //crée une copie de la table d'environnement
    int envp_index;
    int tab_index;
    int i;

    envp_index = 0;
    tab_index = 0;
    i = 0;
    env->tab = (char*)malloc(env->tab_size * sizeof(char));
    if (env->tab == NULL)
    {
        return (-1);
    }
    //copie ta table d'environnment
    while (envp[envp_index] && tab_index < env->tab_size - 1)
    {
        while (envp[envp_index][i] && tab_index < env->tab_size - 1)
        {
            env->tab[tab_index] = envp[envp_index][i];
            tab_index++;
            i++;
        }
        env->tab[tab_index] = '\n';
        tab_index++;
        envp_index++;
        i = 0;
    }
    //Si besoin de plus d'espace
    if (envp[envp_index] != '\0')
        return (1);
    //puis remplie la fin de \0
    while (tab_index < env->tab_size)
    {
        env->tab[tab_index] = '\0';
        tab_index++;
    }
    return 0;
}

// renvoie -1 en cas d'erreur sinon 0
int     init_env(envir *environnement, char **envp)
{
    int loop;

    loop = 1;
    environnement->tab_size = ENVTAB_SIZE;
    if (environnement->tab_size == 0)
    {
        ft_printf("Error Init Env\n");
        return -1;
    }
    while(loop == 1)
    {
        loop = copy_env(environnement, envp);
        if (loop == 1)
        {
            environnement->tab_size += ENVTAB_SIZE;
            free(environnement->tab);
        }
    }
    if (environnement->tab == NULL)
    {
        ft_printf("Error Init Env\n");
        return -1;
    }
    return 0;
}

int main(int argc, char** argv, char **envp)
{
    (void)argc;
    (void)argv;

    envir   environnement;
    char    *var = "NATHAN=beau";
    char    *var1 = "NAT2HAN=beau";

    if (init_env(&environnement, envp) != 0)
        return 0;

    env(&environnement); //print

    //ajouter des variabless
    if (export(&environnement, var) != 0) //add
        ft_printf("Var invalid: %s\n", var);
    if (export(&environnement, var1) != 0) //add
        ft_printf("Var1 invalid: %s\n", var1);
    
    ft_printf("\n\n\n\n");
    env(&environnement); //print
    return 0;
}