/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:22 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/02 17:42:57 by dcota-pa         ###   ########.fr       */
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

int	run_exit(t_command *cmd, int cmd_n, b_tree *tree, int flag)
{
	if (flag)
	{
		free_char_pp(cmd[cmd_n].args);
		free(cmd);
		destroy_tree(&tree);
		get_set_env(NULL, 1, 0);
		exit(0);
	}
	else
		exit(0);
}
