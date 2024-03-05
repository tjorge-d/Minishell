#include "../minishell.h"

int	print_skip_apo(char *str)
{
	int	i;

	i = 1;
	while (str[i] && str[i] != '\'')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '\'')
	{
		i ++;
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
	n_chars_printed = 0;
	while (s[i] && s[i] != ' ' && s[i] != '\t' && s[i] != '\'' && s[i] != '"')
		i++;
	variable = ft_strdup(s);
	if (i > 0)
		value_to_print = get_var_from_env(variable, i);
	if (value_to_print)
	{
		n_chars_printed = ft_printf("%s", value_to_print) + 1;
	}
	free(variable);
	return (i + 1);
}
int	print_no_skips(char *str)
{
	int	i;

	i = 1;
	while(str[i] && str[i] != '"')
	{	
		if(str[i] == '$')
			i += search_and_print_variable(&str[i + 1]);
		if(str[i])
			write(1, &str[i], 1);
		else
			return(0);
		i++;
	}
	if(str[i] == '"')
	{
		write(1, "\"", 1);
		i ++;
	}
	return (i + 1);
}
void	ft_echo(char *str, int flag)
{
	int	i;

	i = 0;
	if(!str)
		return ;
	while(str[i])
	{
		if (str[i] == '"')
			i += print_no_skips(&str[i]);
		if(str[i] == '$')
			i += search_and_print_variable(&str[i + 1]);
		if(str[i] == '\'')
			i += print_skip_apo(&str[i]);
		if(str[i])
			write(1, &str[i], 1);
		else
			break;
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	exit(0);
}


