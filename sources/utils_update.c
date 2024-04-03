/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 17:53:39 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/03 19:32:00 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*search_var_value(char *var_name)
{
	int		index;
	char	*var_value;
	char	**env;

	env = get_set_env(NULL, 0, 0);
	if (!env)
		return (g_var = -1, NULL);
	index = search_var_index(var_name);
	if (index == -1)
		return (NULL);
	var_value = env[index];
	index = 0;
	while (var_value[index] && var_value[index] != '=')
		index ++;
	if (var_value[index] == '=')
		index ++;
	return (&var_value[index]);
}

void	copy_array_2(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = strdup(src[i]);
		i ++;
	}
	dest[i] = NULL;
}

int	array_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i ++;
	}
	return (i);
}

char	**copy_array(char **src)
{
	int		i;
	char	**new_dest;

	if (!src)
		return (NULL);
	i = 0;
	new_dest = malloc(sizeof(char *) * (array_len(src) + 1));
	while (src[i])
	{
		new_dest[i] = strdup(src[i]);
		i ++;
	}
	new_dest[i] = NULL;
	return (new_dest);
}

char	**get_set_env(char **new_env, int flag_to_free, int flag_to_exit)
{
	static char	**env;

	if (new_env)
	{
		if (flag_to_free)
			free_char_pp(env);
		env = copy_array(new_env);
		if (!env)
			return (NULL);
	}
	else if (flag_to_free == 1)
		free_char_pp(env);
	if (flag_to_exit)
		exit(flag_to_free);
	return (env);
}
