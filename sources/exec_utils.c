/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:55 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/02 17:10:30 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	red_in(b_tree *tree, int *fd_in)
{
	int		fd;
	char	*error_msg;

	fd = open(tree->data, O_RDONLY);
	if (fd == -1)
	{
		error_msg = ft_strjoin("ERROR COULD NOT OPEN OR FIND FILE :" \
			, tree->data, 0, 0);
		ft_putstr_fd(error_msg, 2);
		free(error_msg);
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

int	red_in_doc(b_tree *tree, int *fd_in)
{
	int	atoi;

	atoi = ft_atoi(tree->data);
	*fd_in = atoi;
	return (1);
}

int	red_out(b_tree *tree, int *fd_out)
{
	int		fd;
	char	*error_msg;

	fd = open(tree->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("ERROR COULD NOT OPEN :", tree->data, 0, 0);
		ft_putstr_fd(error_msg, 2);
		free(error_msg);
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

int	red_out_app(b_tree *tree, int *fd_out)
{
	int		fd;
	char	*error_msg;

	fd = open(tree->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		error_msg = ft_strjoin("ERROR COULD NOT OPEN :", tree->data, 0, 0);
		ft_putstr_fd(error_msg, 2);
		free(error_msg);
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

char	**build_args(b_tree *tree)
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
