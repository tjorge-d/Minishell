#include "../minishell.h"

char **get_set_env(char **new_env)
{
	static char **env;

	if (new_env)
	{
		//free_char_pp(env);
		env = new_env;
	}
	return (env);
}
