#include "../minishell.h"

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
	var_value = env[index];
	index = 0;
	while (var_value[index] && var_value[index] != '=')
		index ++;
	if (var_value[index] == '=')
		index ++;
	return (&var_value[index]);
}