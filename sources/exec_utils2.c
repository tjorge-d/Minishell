/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:11 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/04 11:53:54 by tjorge-d         ###   ########.fr       */
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
//NOVO
int	ft_is_file(char *command)
{
	int		i;
	
	i = 0;
	while(command[i])
	{
		if (command[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
//NOVO
void	run(t_cmd *cmds, int cmd_n, int total_cmds, t_tree *tree)
{
	dup2(cmds[cmd_n].fd_in, STDIN_FILENO);
	if (cmds[cmd_n].fd_out != 1)
		dup2(cmds[cmd_n].fd_out, STDOUT_FILENO);
	close_fds(cmds, total_cmds);
	if (!is_built_in(cmds[cmd_n].command))
	{
		execve(cmds[cmd_n].command, cmds[cmd_n].args, get_set_env(NULL, 0, 0));
		if (access(cmds[cmd_n].command, X_OK) == 0 && !ft_is_file(cmds[cmd_n].command))	
			perror(cmds[cmd_n].command);
		else if (opendir(cmds[cmd_n].command))
		{
			ft_putstr_fd(cmds[cmd_n].command, 2);
			ft_putstr_fd(": Is a directory\n", 2);
			free_all(total_cmds, cmds, tree, 1);
			get_set_env(NULL, 1, 0);
			exit(126);
		}
		else
		{
			ft_putstr_fd(cmds[cmd_n].command, 2);
			if (ft_is_file(cmds[cmd_n].command))
				ft_putstr_fd(": No such file or directory\n", 2);
			else
				ft_putstr_fd(": command not found\n", 2);
		}
		free_all(total_cmds, cmds, tree, 1);
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
	
	if(!do_redirects(tree, cmd, cmd_n))
		return (free_all(cmd_n, cmd, tree, 0), g_var = 1, 1);
	cmd[cmd_n].args = args;
	ans = 2;
	cmd[cmd_n].std_out = dup(STDOUT_FILENO);
	cmd[cmd_n].std_in = dup(STDIN_FILENO);
	if (cmd[cmd_n].fd_out != 1)
		dup2(cmd[cmd_n].fd_out, STDOUT_FILENO);
	if (cmd[cmd_n].fd_in != 1)
		dup2(cmd[cmd_n].fd_in, STDIN_FILENO);
	close_fds(cmd, 1);
	ans = if_built_in_sequence (cmd, cmd_n, tree, 1);
	if (cmd[cmd_n].std_out && cmd[cmd_n].std_out != STDOUT_FILENO)
	{	
		dup2(cmd[cmd_n].std_out, STDOUT_FILENO);
		close(cmd[cmd_n].std_out);
	}
	if (cmd[cmd_n].std_in && cmd[cmd_n].std_in != STDIN_FILENO)
	{	
		dup2(cmd[cmd_n].std_in, STDIN_FILENO);
		close(cmd[cmd_n].std_in);
	}
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
