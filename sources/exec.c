/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:16 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/02 17:52:20 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_n_commands(b_tree *tree)
{
	int	ans;

	ans = 0;
	while (tree)
	{
		tree = tree->left;
		ans ++;
	}
	return (ans);
}

int	create_pipes(int n_commands, t_command *commands, b_tree *tree)
{
	int	i;
	int	pipes[2];

	i = 0;
	while (i < n_commands)
	{
		if (i == 0)
			commands[i].fd_in = 0;
		if (n_commands != 1)
		{
<<<<<<< HEAD
			if(pipe(pipes) == -1)
					return (free_all(n_commands, commands, tree), \
						fail_msg('P'), g_var = 126, \
						get_set_env(NULL, 1, 126), 0);
=======
			if (pipe(pipes) == -1)
				return (free_all(n_commands, commands, tree), \
					failure_msg('P'), global_var = 126, \
					get_set_env(NULL, 1, 126), 0);
>>>>>>> main
		}
		if (i == n_commands - 1)
			commands[i].fd_out = 1;
		else
		{
			commands[i].fd_out = pipes[1];
			commands[i + 1].fd_in = pipes[0];
		}
		i ++;
	}
	return (1);
}

int	do_redirects(b_tree *tree, t_command *commands, int command_n)
{
	while (tree && tree->type != PIPE)
	{
		if (tree->type == REDIRECT_IN)
		{
			if (red_in(tree, &commands[command_n].fd_in) == 0)
				return (0);
		}
		else if (tree->type == REDIRECT_IN_DOC)
			red_in_doc(tree, &commands[command_n].fd_in);
		else if (tree->type == REDIRECT_OUT)
		{
			if (!red_out(tree, &commands[command_n].fd_out))
				return (0);
		}
		else if (tree->type == REDIRECT_OUT_APP)
		{
			if (!red_out_app(tree, &commands[command_n].fd_out))
				return (0);
		}
		tree = tree->right;
	}
	return (1);
}

void	do_child(b_tree *tree, int command_n, t_command *commands, int total)
{
	if ((tree->type == PIPE || tree->type == FIRST_BRANCH))
	{
		tree = tree->right;
		if (!do_redirects(tree, commands, command_n))
			return ;
		while (tree && (tree->type != COMMAND))
			tree = tree->right;
		if (tree)
			run(commands, command_n, total, tree);
	}
}

int	executor(b_tree *tree)
{
	int			n_commands;
	t_command	*cmds;
	int			i;

	i = -1;
	n_commands = get_n_commands(tree);
	cmds = malloc(sizeof(t_command) * n_commands);
	fill_commands(n_commands, cmds, tree);
	create_pipes(n_commands, cmds, tree);
	if (n_commands == 1 && cmds[0].command && is_built_in(cmds[0].command))
		return (run_built_in_solo(tree, cmds, build_args(tree), 0));
	while (++i < n_commands)
	{
		cmds[i].args = build_args(tree);
		cmds[i].process_id = fork();
		if (!cmds[i].process_id)
			do_child(tree, i, cmds, n_commands);
		else if (cmds[i].process_id < 0)
			return (failure_msg('F'), free_all(n_commands, cmds, tree),
				g_var = 126, get_set_env(NULL, 1, 126), 126);
		else
			tree = tree->left;
	}
	close_fds(cmds, n_commands);
	return (wait_loop(n_commands, cmds));
}
