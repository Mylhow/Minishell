/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_manager.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourbou <abourbou@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:26:14 by abourbou          #+#    #+#             */
/*   Updated: 2020/12/18 11:16:43 by abourbou         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_MANAGER_H
# define SIGNAL_MANAGER_H

void	signal_main(int signal);

int		g_interrupt;
int		g_passed;
int		g_piped;
#endif
