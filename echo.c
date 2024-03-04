#include "minishell.h";

char *get_var_from_env(char *var, int len)
{
	char	**env;
	int		i;

	env = get_env();
	while (env[i])
	{
		if(!ft_strncmp(var, env[i], len))
		{
			return (&env[len + 1]);
		}
		i ++;
	}
	return (NULL);
}

int	search_and_print_variable(char *s)
{
	int i;
	char *variable;
	char *value_to_print;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	ft_strlcopy(variable, s, i);
	if (i > 0)
		value_to_print = get_var_from_env(variable, i);
	if (value_to_print)
		return(ft_printf(value_to_print) + 1);
	else 
		return(ft_printf("\n"));
}

void ft_echo(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '$')
			i += search_and_print_variable(&str[i + 1]);
		if(str[i])
			write(1, &str[i], 1);
		else
			exit(0);
		i++;
	}
	exit(0);
}

char **get_env(void)
{
	static char **env;

	return (env);
}