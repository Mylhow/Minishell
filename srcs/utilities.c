/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgascon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 09:39:22 by dgascon           #+#    #+#             */
/*   Updated: 2020/12/18 09:39:23 by dgascon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "terminal.h"

/*
 ** Renvoie un pointeur sur la structure du terminal
 ** Return [**t_term] structure du terminal
*/

t_term		**getterm(void)
{
	static t_term *term;

	return (&term);
}
