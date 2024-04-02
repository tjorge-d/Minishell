/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_exp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:08 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/02 16:47:28 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_declare(void)
{
	char	**env;
	int		i;

	i = 0;
	env = get_set_env(NULL, 0, 0);
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

int	validate_expression(char *expression)
{
	int	i;

	i = 0;
	if (ft_isalpha(expression[i]) || expression[i] == '_')
	{
		i++;
		while (expression[i] && expression[i] != '=')
		{
			if (ft_isalnum(expression[i]) || expression[i] == '_')
				i++;
			else
				return (0);
		}
	}
	else
		return (0);
	return (1);
}

int	search_var_index(char *s)
{
	int		i;
	int		j;
	char	*var_c;
	char	*var;
	char	**env;

	i = 0;
	env = get_set_env(NULL, 0, 0);
	j = -1;
	while (s[i] && s[i] != '=')
		i++;
	var = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var, s, i + 1);
	var_c = ft_strjoin(var, "=", 0, 0);
	while (env[++j])
	{
		if (!ft_strncmp(var_c, env[j], i + 1)
			|| !ft_strncmp(var, env[j], i + 1))
		{
			free(ft_strjoin(var, var_c, 1, 1));
			return (j);
		}
	}
	free(ft_strjoin(var, var_c, 1, 1));
	return (-1);
}

int	export(char *expression)
{
	char	**env;
	char	**new_env;
	int		old_loc;

	env = get_set_env(NULL, 0, 0);
	if (!validate_expression(expression))
		return (-1);
	old_loc = search_var_index(expression);
	if (old_loc == -1)
	{
		new_env = malloc(sizeof(char *) * (array_len(env) + 2));
		if (!new_env)
			return (0);
		copy_array_2(env, new_env);
		new_env[array_len(env)] = strdup(expression);
		new_env[array_len(env) + 1] = NULL;
		get_set_env(new_env, 1, 0);
		free_char_pp(new_env);
		return (1);
	}
	free(env[old_loc]);
	env[old_loc] = strdup(expression);
	return (1);
}

int	run_exp(char **args)
{
	int	i;
	int	res;

	i = 1;
	if (args && !args[i])
	{
		return (print_declare());
	}
	while (args[i])
	{
		res = export(args[i]);
		if (res == -1)
		{
			ft_putstr_fd("export:", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd(": not a valid identifier\n", 2);
		}
		i ++;
	}
	return (res);
}
