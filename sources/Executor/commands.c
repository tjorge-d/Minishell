/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:40:15 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/10 17:18:31 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	get_n_commands(t_tree *tree)
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
	while (tree && tree->type != COMMAND)
	{
		tree = tree->right;
	}
	if (tree)
		commands[n_cmd].command = tree->data;
	else
		commands[n_cmd].command = NULL;
}

int	build_args(int cmd_n, t_cmd *commands, t_tree *tree)
{
	char	**args;
	int		i;

	i = 0;
	if (commands[cmd_n].command == NULL)
	{
		args = malloc(sizeof(char *));
		args[0] = NULL;
		commands[cmd_n].args = args;
		return (1);
	}
	while (tree && (tree->type != COMMAND))
		tree = tree->right;
	args = malloc(sizeof(char *) *(count_args(tree) + 1));
	if (!args)
		return (0);
	while (tree && (tree->type == COMMAND || tree->type == ARGUMENT))
	{
		args[i++] = strdup(tree->data);
		tree = tree->right;
	}
	args[i] = NULL;
	commands[cmd_n].args = args;
	return (1);
}

void	fill_commands(int n_commands, t_cmd *commands, t_tree *tree)
{
	int	i;

	i = 0;
	while (i < n_commands)
	{
		fill_command(i, commands, tree);
		build_args(i, commands, tree);
		i++;
		tree = tree->left;
	}
}
