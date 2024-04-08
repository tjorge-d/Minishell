/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:54:51 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/08 17:18:25 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quit_here_doc(int signal)
{
	close(0);
	g_var = 130;
	(void)signal;
}

void	ctrl_c_proccess(int signal)
{
	printf("\n");
	(void)signal;
}

void	ctrl_c_signal_hd(int signal)
{
	g_var = 130;
	(void)signal;
}

void	ctrl_c_signal(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_var = 130;
	(void)signal;
}
