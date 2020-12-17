/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sigquit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:30:10 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/17 17:42:57 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft_printf.h"
#include "expander.h"

void	handle_sigquit(void)
{
	if (g_exit_status % 255 == 131)
		ft_printf("Quit (core dumped)\n");
}