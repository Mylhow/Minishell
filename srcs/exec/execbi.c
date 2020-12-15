/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execbi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 10:06:18 by lrobino           #+#    #+#             */
/*   Updated: 2020/12/15 09:24:11 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int  strplen(char **strp)
{
    int i = 0;

    while (strp[i])
        i++;
    return (i);
}

int         execbi(char *name, char **argv)
{
    exec_builtin exec;

    if (!(exec = is_builtin(name)))
        return (1);
    return (exec (strplen(argv), argv, g_envp));
}