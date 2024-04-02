/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:36 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/02 16:57:42 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i ++;
	}
	return (0);
}

int	print_env(void)
{
	char	**env;
	int		i;

	i = 0;
	env = get_set_env(NULL, 0, 0);
	while (env[i])
	{
		if (has_equal(env[i]))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}

int	run_env(char **args)
{
	if (args[1])
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	else 
		return (print_env());
}
