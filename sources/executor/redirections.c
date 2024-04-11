/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:55 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/10 17:18:23 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	red_in(t_tree *tree, int *fd_in)
{
	int		fd;

	fd = open(tree->data, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(tree->data, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_var = 1;
		return (0);
	}
	else
	{
		if (*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in = fd;
		return (1);
	}
}

int	red_in_doc(t_tree *tree, int *fd_in)
{
	int	fd;

	fd = ft_atoi(tree->data);
	if (*fd_in != STDIN_FILENO)
		close(*fd_in);
	*fd_in = fd;
	return (1);
}

int	red_out(t_tree *tree, int *fd_out)
{
	int		fd;

	fd = open(tree->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(tree->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	else
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = fd;
		return (1);
	}
}

int	red_out_app(t_tree *tree, int *fd_out)
{
	int		fd;

	fd = open(tree->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Error: ", 2);
		ft_putstr_fd(tree->data, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	else
	{
		if (*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out = fd;
		return (1);
	}
}

int	do_redirects(t_tree *tree, t_cmd *commands, int command_n)
{
	while (tree && tree->type != PIPE)
	{
		if (tree->type == REDIRECT_IN)
		{
			if (!red_in(tree, &commands[command_n].fd_in))
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
