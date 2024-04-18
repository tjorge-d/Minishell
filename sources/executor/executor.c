/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:16 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/18 16:53:37 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	create_pipes(int n_commands, t_cmd *commands, t_tree *tree)
{
	int	i;
	int	pipes[2];

	i = 1;
	commands[0].fd_in = 0;
	commands[n_commands - 1].fd_out = 1;
	while (i < n_commands)
	{
		if (pipe(pipes) == -1)
			return (free_all(n_commands, commands, tree, 1), \
				fail_msg('P'), g_var = 126, \
				get_set_env(NULL, 1, 126), 0);
		commands[i - 1].fd_out = pipes[1];
		commands[i].fd_in = pipes[0];
		i++;
	}
	return (1);
}

int	do_child(t_tree *tree, int command_n, t_cmd *commands, int total)
{
	int		j;
	t_tree	*head;

	j = -1;
	head = tree;
	while (++j < command_n)
		head = head->left;
	if ((head->type == PIPE || head->type == FIRST_BRANCH))
	{
		if (head->right == NULL)
			return (free_all(total, commands, tree, 1), \
				get_set_env(NULL, 1, 0), exit(0), 0);
		head = head->right;
		if (!do_redirects(head, commands, command_n))
			return (free_all(total, commands, tree, 1), \
				get_set_env(NULL, 1, 0), exit(1), 1);
		while (head && (head->type != COMMAND))
			head = head->right;
		if (head)
			run(commands, command_n, total, tree);
		else
			return (get_set_env(NULL, 1, 0), \
				free_all(total, commands, tree, 1), exit(0), 0);
	}
	return (0);
}

int	executor(t_tree *tree)
{
	int			n_commands;
	t_cmd		*cmds;
	int			i;

	i = -1;
	n_commands = get_n_commands(tree);
	cmds = ft_calloc(n_commands, sizeof(t_cmd));
	fill_commands(n_commands, cmds, tree);
	create_pipes(n_commands, cmds, tree);
	if (n_commands == 1 && cmds[0].command && is_built_in(cmds[0].command))
		return (run_built_in_solo(tree, cmds, cmds[0].args, 0));
	while (++i < n_commands)
	{
		cmds[i].process_id = fork();
		if (cmds[i].process_id == 0)
		{
			signal(SIGINT, ctrl_c_proccess);
			do_child(tree, i, cmds, n_commands);
		}
		else if (cmds[i].process_id < 0)
			return (fail_msg('F'), free_all(n_commands, cmds, tree, 1),
				g_var = 126, get_set_env(NULL, 1, 126), 126);
	}
	close_fds(cmds, n_commands);
	return (wait_loop(n_commands, cmds));
}
