#include "../minishell.h"

void	print_array(char **arr)
{
	int	i;

	i = 0;
	if(arr && arr[i])
	{
		while (arr[i])
		{
			printf("%s\n", arr[i]);
			i ++;
		}
	}
}

char *search_var_value(char *var_name)
{
	int		index;
	char	*var_value;
	char	**env;

	env = get_set_env(NULL, 0);
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

int	array_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i ++;
	return (i);
}

char	**copy_array(char **src)
{
	int	i;
	char **new_dest;

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
	return(new_dest);
}

void	free_char_pp(char **array)
{
	int	i;

	i = 0;
	printf("IN FREE %p\n", array);
	if (array && array[i])
	{
		while (array[i])
		{
			free(array[i]);
			i ++;
		}
	}
	free(array);
}

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