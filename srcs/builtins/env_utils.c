#include "env.h"

envir   *dup_env_var(envir *var)
{
    envir *new;

    if (!(new = malloc(sizeof(envir))))
        return NULL;
    if (!(new->key = malloc(ft_strlen(var->key))))
        return NULL;
    if (!(new->value = malloc(ft_strlen(var->value))))
        return NULL;
    ft_strlcpy(new->key, var->key, ft_strlen(var->key) + 1);
    ft_strlcpy(new->value, var->value, ft_strlen(var->value) + 1);
    new->next = var->next;
    return new;
}

envir   *dup_env(envir *env)
{
    envir   *new;
    envir   *tmp;

    new = dup_env_var(env);
    tmp = new;
    env = env->next;
    while(env)
    {
        tmp->next = dup_env_var(env);
        tmp = tmp->next;
        env = env->next;
    }
    return new;
}

void    del_env(envir *env)
{
    void    *next;

    while (env)
    {
        free(env->key);
        free(env->value);
        next = env->next;
        free(env);
        env = next;
    }
}

void	add_env_var(envir *env, char *var)
{
	envir *tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	dprintf(1, "ADDING_VAR: %s\n", var);
	tmp->next = new_var(var);
}

void	print_env(envir *env)
{
	envir *tmp;

	if (!env)
		return;
	tmp = env;
	while (tmp->next)
	{
		dprintf(1, "%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	dprintf(1, "%s=%s\n", tmp->key, tmp->value);
}

envir	*new_var(char *var)
{
	envir	*new;
	char	*value;
	int		key_size;

	if (!var)
		return NULL;
	key_size = ft_strichr(var, '=');
	if (key_size == -1)
	{
		key_size = ft_strlen(var);
		value = &var[key_size];
	}
	else
		value = ft_strchr(var, '=') + 1;
	if (!(new = (envir*)malloc(sizeof(envir))))
		return NULL;
	if (!(new->key = (char *)malloc(key_size * sizeof(char) + 1)))
		return NULL;
	if (!(new->value = (char *)malloc(ft_strlen(value) * sizeof(char) + 1)))
		return NULL;
	new->next = NULL;
	ft_strlcpy(new->key, var, key_size);
	ft_strlcpy(new->value, value, ft_strlen(value)+1);
	return new;
}