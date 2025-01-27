/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:31 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/10 16:40:21 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char **strs, int flag)
{
	int	i;

	i = 0;
	if (!strs)
		return (1);
	while (strs[i])
	{
		ft_putstr_fd(strs[i], STDOUT_FILENO);
		i++;
		if (strs[i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!flag)
		write(1, "\n", 1);
	return (0);
}

int	run_echo(char **args)
{
	int	i;
	int	flag;

	i = 1; 
	flag = 0;
	if (!args || !args[0])
		return (1);
	if (!args[i])
		return (printf("\n"), 0);
	while (is_valid_flag(args[i]))
	{
		flag = 1;
		i++;
	}
	return (ft_echo(&args[i], flag));
}

int	is_valid_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] && arg[i] == '-')
		i ++;
	else
		return (0);
	if (arg[i] && arg[i] == 'n')
		i++;
	else 
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i ++;
	}
	return (1);
}
