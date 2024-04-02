/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:31:53 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/02 17:43:38 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_built_in(char *line)
{
	if (!ft_strncmp(line, "echo", 5) \
		|| !ft_strncmp(line, "cd", 3) \
		|| !ft_strncmp(line, "pwd", 4) \
		|| !ft_strncmp(line, "export", 8) \
		|| !ft_strncmp(line, "unset", 6) \
		|| !ft_strncmp(line, "env", 4) \
		|| !ft_strncmp(line, "exit", 5))
		return (1);
	return (0);
}

char	*check_command(char **path, char *data)
{
	int		i;
	char	*new_data;

	i = -1;
	while (path[++i])
	{
		new_data = ft_strjoin(path[i], "/", 0, 0);
		if (new_data == NULL)
			return (free(data), NULL);
		new_data = ft_strjoin(new_data, data, 1, 0);
		if (new_data == NULL)
			return (free(data), NULL);
		if (access(new_data, X_OK) == 0)
		{
			free(data);
			return (new_data);
		}
		else
			free(new_data);
	}
	return (data);
}

char	*get_data_path(char *data, b_tree **tree, t_token **token)
{
	char	**paths;
	char	*path;

	if (is_built_in(data) || data[0] == '\0')
		return (data);
	path = search_var_value("PATH");
	if (!path)
	{
		if (g_var == -1)
			return (destroy_tree(tree), destroy_tokens((*token), 'h'), \
				get_set_env(NULL, 1, 2), NULL);
		return (data);
	}
	paths = ft_split(path, ':');
	if (!paths)
		return (destroy_tree(tree), destroy_tokens((*token), 'h'), \
			fail_msg('M'), get_set_env(NULL, 1, 2), NULL);
	data = check_command(paths, data);
	if (!data)
		return (destroy_tree(tree), destroy_tokens((*token), 'h'), \
			fail_msg('M'), get_set_env(NULL, 1, 2), NULL);
	free_matrix(paths);
	return (data);
}
