#include "../minishell.h"

int	print_declare()
{
	char **env;
	int i;

	i = 0;
	env = get_set_env(NULL, 0);
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
	return (0);
}

int validate_expression(char *expression)
{
	int	i;
	i = 0;
	if(ft_isalpha(expression[i]) || expression[i] == '_')
	{
		i++;
		while (expression[i] && expression[i] != '=')
		{

			if(ft_isalnum(expression[i]) || expression[i] == '_')
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
	int		env_counter;
	char	*var_complete;
	char	*variable;
	char	**env;

	i = 0;
	env = get_set_env(NULL, 0);
	env_counter = -1;
	variable = NULL;
	while (s[i] && s[i] != '=')
		i++;
	variable = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(variable, s, i + 1);
	var_complete = ft_strjoin(variable, "=", 1, 0);
	while (env[++env_counter])
	{
		if(!ft_strncmp(var_complete, env[env_counter], i + 1))
		{	
			free(var_complete);
			return (env_counter);
		}
	}
	free(var_complete);
	return (-1);
}

int	export(char *expression)
{
	char	**env;
	char	**new_env;
	int		old_loc;

	env = get_set_env(NULL, 0);
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
		get_set_env(new_env,1);
		free_char_pp(new_env);
		return (1);
	}
	free(env[old_loc]);
	env[old_loc] = expression;
	get_set_env(env, 0);
	return (1);
}

int	run_exp(char **args)
{
	int	i;
	int res;

	i = 1;
	if (args && !args[1])
	{
		return (print_declare());
	}
	while (args[i])
	{
		res = export(args[1]);
		if (res == -1)
		{
			ft_putstr_fd("export:",2);
			ft_putstr_fd(args[i],2);
			ft_putstr_fd(": not a valid identifier\n",2);
		}
		i ++;
	}
	return (res);
}
