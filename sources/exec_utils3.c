/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:40:15 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/05 11:57:47 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_is_command(char *command)
{
	int		i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '/')
			return (0);
		i++;
	}
	return (1);
}

void	fill_command(int n_cmd, t_cmd *commands, t_tree *tree)
{
	int	i;

	i = 0;
	while (i < n_cmd)
	{
		tree = tree->left;
		i ++;
	}
	while (tree && tree->type != COMMAND)
	{
		tree = tree->right;
	}
	if (tree)
		commands[n_cmd].command = tree->data;
}

void	fill_commands(int n_commands, t_cmd *commands, t_tree *tree)
{
	int	i;

	i = 0;
	while (i < n_commands)
	{
		fill_command(i, commands, tree);
		i++;
	}
}

void	close_fds(t_cmd *coms, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (coms[i].fd_in != STDIN_FILENO)
			close(coms[i].fd_in);
		if (coms[i].fd_out != STDOUT_FILENO)
			close(coms[i].fd_out);
		i++;
	}
}
