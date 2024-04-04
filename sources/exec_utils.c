/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:55 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/04 16:05:35 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int	atoi;

	atoi = ft_atoi(tree->data);
	*fd_in = atoi;
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

char	**build_args(t_tree *tree)
{
	char	**args;
	int		i;

	i = 0;
	while (tree && (tree->type != COMMAND))
		tree = tree->right;
	if (tree)
	{
		args = malloc(sizeof(char *) *(count_args(tree) + 1));
		if (!args)
			return (NULL);
		while (tree && (tree->type == COMMAND || tree->type == ARGUMENT))
		{
			args[i++] = strdup(tree->data);
			tree = tree->right;
		}
		args[i] = NULL;
	}
	else
		return (NULL);
	return (args);
}
