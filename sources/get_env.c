#include "../minishell.h"

char **get_set_env(char ***new_env, int flag_to_free)
{
	static char **env;
	if (new_env)
	{
		if(flag_to_free)
			free_char_pp(env);
		env = copy_array(*new_env);
	}
	else if(flag_to_free == 1)
	{
		free_char_pp(env);
	}
	return (env);
}

int	set_env_pwd(char *new_pwd)
{
	export(ft_strjoin("PWD=", new_pwd, 0, 0));
	return(1);
}
int	set_env_old_pwd(char *new_old_pwd)
{
	export(ft_strjoin("OLDPWD=", new_old_pwd, 0, 0));
	return(1);
}