/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:11 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/03 12:26:33 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_args(t_tree *tree)
{
	int	i;

	i = 0;
	while (tree && (tree->type == COMMAND || tree->type == ARGUMENT))
	{
		i ++;
		tree = tree->right;
	}
	return (i);
}

void	run(t_cmd *cmds, int cmd_n, int total_cmds, t_tree *tree)
{
	char	*error_msg;

	dup2(cmds[cmd_n].fd_in, STDIN_FILENO);
	if (cmds[cmd_n].fd_out != 1)
		dup2(cmds[cmd_n].fd_out, STDOUT_FILENO);
	close_fds(cmds, total_cmds);
	if (!is_built_in(cmds[cmd_n].command))
	{
		execve(cmds[cmd_n].command, cmds[cmd_n].args, get_set_env(NULL, 0, 0));
		if (access(cmds[cmd_n].command, X_OK) == 0)
			perror(cmds[cmd_n].command);
		else
		{
			error_msg = ft_strjoin(cmds[cmd_n].command, \
				": Command not found\n", 0, 0);
			ft_putstr_fd(error_msg, 2);
			free(error_msg);
		}
		free_all(total_cmds, cmds, tree);
		get_set_env(NULL, 1, 0);
		exit(127);
	}
	else 
		exit(run_built_in(cmds, cmd_n, tree));
}

int	if_built_in_sequence(t_cmd *cmd, int cmd_n, t_tree *tree, int flag)
{
	if (!ft_strncmp(cmd[cmd_n].command, "echo", 5))
		return (run_echo(cmd[cmd_n].args));
	else if (!ft_strncmp(cmd[cmd_n].command, "cd", 3))
		return (run_cd(cmd[cmd_n].args));
	else if (!ft_strncmp(cmd[cmd_n].command, "pwd", 4))
		return (print_pwd());
	else if (!ft_strncmp(cmd[cmd_n].command, "export", 8))
		return (run_exp(cmd[cmd_n].args));
	else if (!ft_strncmp(cmd[cmd_n].command, "unset", 6))
		return (run_unset(cmd[cmd_n].args));
	else if (!ft_strncmp(cmd[cmd_n].command, "env", 4))
		return (run_env(cmd[cmd_n].args));
	else if (!ft_strncmp(cmd[cmd_n].command, "exit", 5))
		return (run_exit(cmd, cmd_n, tree, flag));
	return (-1);
}

int	run_built_in_solo(t_tree *tree, t_cmd *cmd, char **args, int cmd_n)
{
	int	ans;
	int	temp1;
	int	temp2;

	do_redirects(tree, cmd, cmd_n);
	cmd[cmd_n].args = args;
	ans = 2;
	temp1 = dup(STDIN_FILENO);
	temp2 = dup(STDOUT_FILENO);
	dup2(cmd[cmd_n].fd_in, STDIN_FILENO);
	if (cmd[cmd_n].fd_out != 1)
		dup2(cmd[cmd_n].fd_out, STDOUT_FILENO);
	close_fds(cmd, 1);
	ans = if_built_in_sequence (cmd, cmd_n, tree, 1);
	if (temp1 != STDIN_FILENO)
		dup2(temp1, STDIN_FILENO);
	if (temp2 != STDOUT_FILENO)
		dup2(temp2, STDOUT_FILENO);
	free_char_pp(cmd[cmd_n].args);
	free(cmd);
	return (ans);
}

int	run_built_in(t_cmd *cmd, int cmd_n, t_tree *tree)
{
	int	ans;

	ans = if_built_in_sequence(cmd, cmd_n, tree, 0);
	return (ans);
}
