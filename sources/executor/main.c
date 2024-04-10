/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 20:01:53 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/10 20:09:24 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_var;

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

int	runner(void)
{
	t_tree	*tree;
	char	*line;

	tree = NULL;
	signal(SIGINT, ctrl_c_signal);
	signal(SIGQUIT, SIG_IGN);
	line = readline("Minishell> ");
	if (!line)
		return (printf("exit\n"), 0);
	if (line[0] == '\0')
		return (free(line), 1);
	add_history(line);
	tree = parser(line);
	if (!tree)
		return (1);
	if (tree)
	{
		signal(SIGINT, ctrl_c_proccess);
		signal(SIGQUIT, SIG_DFL);
		g_var = executor(tree);
		destroy_tree(&tree);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	g_var = 0;
	get_set_env(envp, 0, 0);
	increase_shell_lvl();
	while (runner())
		;
	rl_clear_history();
	get_set_env(NULL, 1, 0);
	return (0);
}
// valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  
// --suppressions=".valgrind.supp" ./minishell
