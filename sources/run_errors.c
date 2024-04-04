/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:58:56 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/04 15:59:42 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dir_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n)
{
	DIR	*dir_n;

	dir_n = opendir(cmds[cmd_n].command);
	if (dir_n)
	{
		closedir(dir_n);
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(cmds[cmd_n].command, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_all(ttl_cmds, cmds, tree, 1);
		get_set_env(NULL, 1, 0);
		exit(126);
	}
}

void	cmd_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n)
{
	ft_putstr_fd(cmds[cmd_n].command, 2);
	ft_putstr_fd(": command not found\n", 2);
	free_all(ttl_cmds, cmds, tree, 1);
	get_set_env(NULL, 1, 0);
	exit(127);
}

void	fl_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n)
{
	if (access(cmds[cmd_n].command, F_OK))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(cmds[cmd_n].command, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_all(ttl_cmds, cmds, tree, 1);
		get_set_env(NULL, 1, 0);
		exit(127);
	}
	if (access(cmds[cmd_n].command, X_OK))
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(cmds[cmd_n].command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free_all(ttl_cmds, cmds, tree, 1);
		get_set_env(NULL, 1, 0);
		exit(126);
	}
	free_all(ttl_cmds, cmds, tree, 1);
	get_set_env(NULL, 1, 0);
	exit(127);
}
