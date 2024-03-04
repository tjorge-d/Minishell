#include "../minishell.h"

int	print_skip_apo(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '\'')
	{
		i ++;
		write(1, "'", 1);
	}
	return (i);
}

char *get_var_from_env(char *var, int len)
{
	char	**env;
	int		i;

	i = 0;
	env = get_set_env(NULL);
	while (env[i])
	{
		if(!ft_strncmp(var, env[i], len))
		{
			return (&env[i][len + 1]);
		}
		i ++;
	}
	return (NULL);
}

int	search_and_print_variable(char *s)
{
	int		i;
	int		n_chars_printed;
	char	*variable;
	char 	*value_to_print;

	value_to_print = NULL;
	variable = NULL;
	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t')
		i++;
	variable = ft_strdup(s);
	if (i > 0)
		value_to_print = get_var_from_env(variable, i);
	if (value_to_print)
	{
		n_chars_printed = printf("%s", value_to_print) + 1;
	}
	else 
		n_chars_printed = printf("\n");
	free(variable);
	return (n_chars_printed);
}
void	ft_echo_withskips(char *str)
{
	int	i;

	i = 0;
	printf("%s\n", str);
	if(!str)
		return ;
	while(str[i])
	{
		if(str[i] == '\'')
		{
			print_skip_apo(&str[i]);
		}
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

void	ft_echo_noskips(char *str)
{
	int	i;

	i = 0;
	printf("%s\n", str);
	if(!str)
		return ;
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

