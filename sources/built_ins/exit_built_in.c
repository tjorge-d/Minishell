/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_built_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:22 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/11 11:46:31 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	run_exit(t_cmd *cmd, int cmd_n, t_tree *tree, int flag)
{
	long	ans;

	ans = 0;
	if (flag)
	{
		ft_putstr_fd("exit\n", cmd[cmd_n].std_out);
		close(cmd[cmd_n].std_in);
		close(cmd[cmd_n].std_out);
	}
	if (cmd[cmd_n].args[1] && !cmd[cmd_n].args[2])
	{
		ans = ft_exit_atoi(cmd[cmd_n].args[1]);
	}
	else if (cmd[cmd_n].args[1] && cmd[cmd_n].args[2])
		return (ft_putstr_fd("Error: exit: too many arguments\n", 2), 1);
	if (ans == LONG_MAX)
	{
		ft_putstr_fd("Error: exit: numeric argument required\n", 2);
		ans = 2;
	}
	return (ans = (unsigned char)ans, \
		free_all(get_n_commands(tree), cmd, tree, 1), \
		g_var = ans, get_set_env(NULL, 1, 0), exit(ans), ans);
}
