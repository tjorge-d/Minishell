/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:22 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/08 17:45:52 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	increase_shell_lvl(void)
{
	char	*shlvl_str;
	int		shlvl;
	int		index;
	char	**env;

	shlvl_str = search_var_value("SHLVL");
	if (!shlvl_str)
		export(strdup("SHLVL=1"));
	else
	{
		shlvl = ft_atoi(shlvl_str);
		shlvl++;
		shlvl_str = ft_itoa(shlvl);
		shlvl_str = ft_strjoin("SHLVL=", shlvl_str, 0, 1);
		index = search_var_index("SHLVL");
		env = get_set_env(NULL, 0, 0);
		free(env[index]);
		env[index] = shlvl_str;
	}
}

int	run_exit(t_cmd *cmd, int cmd_n, t_tree *tree, int flag)
{
	long	ans;

	ans = 0;
	if (flag)
		ft_putstr_fd("exit\n", cmd[cmd_n].std_out);
	if (cmd[cmd_n].args[1] && !cmd[cmd_n].args[2])
	{
		ans = ft_exit_atoi(cmd[cmd_n].args[1]);
	}
	else if (cmd[cmd_n].args[1] && cmd[cmd_n].args[2])
		return (ft_putstr_fd("Error: exit: too many arguments\n", 2), 1);
	if (flag)
	{
		if (ans == LONG_MAX)
		{
			ft_putstr_fd("Error: exit: numeric argument required\n", 2);
			ans = 2;
		}
		return (ans = (unsigned char)ans, close(cmd[cmd_n].std_out), \
			free_all(1, cmd, tree, 1), \
			g_var = ans, get_set_env(NULL, 1, 0), exit(ans), ans);
	}
	else
		return (ans = (unsigned char) ans, g_var = ans, exit(ans), ans);
}
