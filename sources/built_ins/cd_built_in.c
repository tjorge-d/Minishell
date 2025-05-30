/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:25 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/10 16:40:31 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*get_error_msg_cd(char *arg)
{
	char	*temp;

	temp = ft_strjoin("Error: cd: ", arg, 0, 0);
	return (ft_strjoin(temp, ": ", 1, 0));
}

void	ft_chdir_our_env(char *new_dir)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strjoin("OLDPWD=", search_var_value("PWD"), 0, 0);
	temp2 = ft_strjoin("PWD=", new_dir, 0, 0);
	export (temp1);
	export (temp2);
	free(temp1);
	free(temp2);
}

int	cd_without_args(void)
{
	char	*error_msg;
	char	*home_value;
	char	*cwd;	

	home_value = search_var_value("HOME");
	if (!home_value)
		return (ft_putstr_fd("bash: cd: HOME not set\n", 2), 1);
	if (chdir(home_value))
	{
		error_msg = get_error_msg_cd(home_value);
		ft_putstr_fd(error_msg, 2);
		free(error_msg);
		perror(NULL);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	ft_chdir_our_env(cwd);
	free(cwd);
	return (0);
}

int	cd_with_arg(char *arg)
{
	char	*error_msg;
	char	*cwd;

	if (!arg)
		return (ft_putstr_fd("bash: cd: OLDPWD not set\n", 2), 1);
	if (!ft_strncmp("-", arg, 2))
	{
		return (cd_with_arg(search_var_value("OLDPWD")));
	}
	else if (chdir(arg))
	{
		error_msg = get_error_msg_cd(arg);
		ft_putstr_fd(error_msg, 2);
		free(error_msg);
		perror(NULL);
		return (1);
	}
	cwd = getcwd(NULL, 0);
	ft_chdir_our_env(cwd);
	free(cwd);
	return (0);
}

int	run_cd(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i ++;
	if (i > 2)
	{
		ft_putstr_fd("ERROR: Cd: too many arguments\n", 2);
	}
	else if (i <= 1 || (i == 2 && args[1][0] == '\0'))
	{
		return (cd_without_args());
	}
	else
		return (cd_with_arg(args[1]));
	return (1);
}
