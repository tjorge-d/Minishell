/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:53:28 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/03 12:12:16 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_array_skip(char **src, char **dest, int index)
{
	int	i;

	i = 0;
	while (i < index && src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i ++;
	}
	while (src[i + 1])
	{
		dest[i] = ft_strdup(src[i + 1]);
		i ++;
	}
	dest[i] = NULL;
}

int	unset(char *expression)
{
	char	**env;
	char	**new_env;
	int		loc;

	env = get_set_env(NULL, 0, 0);
	loc = search_var_index(expression);
	if (loc == -1)
	{
		return (0);
	}
	new_env = malloc(sizeof(char *) * (array_len(env)));
	if (!new_env)
		return (2);
	copy_array_skip(env, new_env, loc);
	get_set_env(new_env, 1, 0);
	free_char_pp(new_env);
	return (0);
}

int	run_unset(char **args)
{
	int	i;
	int	res;

	i = 1;
	if (args && !args[i])
	{
		return (0);
	}
	while (args[i])
	{
		res = unset(args[i]);
		i ++;
	}
	return (res);
}
