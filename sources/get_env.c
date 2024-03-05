#include "../minishell.h"

char **get_set_env(char **new_env)
{
	static char **env;

	if (new_env)
	{
		free_char_pp(env);
		env = new_env;
	}
	return (env);
}

int	set_env_pwd(char *new_pwd)
{
	int	i;
	char **env;

	i = 0;
	env = get_set_env(NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PWD=", 4))
		{
			free(env[i]);
			env[i] = new_pwd;
			return (1);
		}
	}
	env[i] = ft_strjoin("PWD=", new_pwd);
	return (1);
}
int	set_env_old_pwd(char *new_old_pwd)
{
	int	i;
	char **env;

	i = 0;
	env = get_set_env(NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "OLDPWD=", 4))
		{
			free(env[i]);
			env[i] = new_old_pwd;
			return (1);
		}
	}
	env[i] = ft_strjoin("OLDPWD=", new_old_pwd);
	return (1);
}