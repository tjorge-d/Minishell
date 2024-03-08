#include "../minishell.h"

char	*add_char(char *old_line, char c, int c_pos)
{
	char	*new_line;
	int		i;

	new_line = malloc(sizeof(char) * (c_pos + 2));
	if (!new_line)
	{
		free(old_line);
		return (NULL);
	}
	i = 0;
	while (i < c_pos)
    {
        new_line[i] = old_line[i];
		i++;
    }
	new_line[i] = c;
	new_line[i + 1] = '\0';
	free(old_line);
	return (new_line);
}

int	add_single_quote(char *expanded_line, char *line, int i)
{
	while (line[i] && line[i] != '\'')
	{
		expanded_line = add_char(expanded_line, line[i], i);
		if (!expanded_line)
			return (-1);
		i++;
	}
	if (str[i] == '\0')
	{
		free(expanded_line);
		write(2, "Error: Invalid sintax\n", 23);
		return (-1);
	}
	expanded_line = add_char(expanded_line, line[i], i);
	if (!expanded_line)
		return (-1);
	return (i + 1);
}

int	add_double_quote(char *expanded_line, char *line, int i)
{
	while(line[i] && line[i] != '"')
	{
		if(str[i] == '$')
			i = search_and_add_variable(&str[i + 1]);
		else
		{
			expanded_line = add_char(expanded_line, line[i], i);
			if (!expanded_line)
				return (-1);
			i++;
		}
		if (i == -1)
			return (-1);
	}
	if (str[i] == '\0')
	{
		free(expanded_line);
		write(2, "Error: Invalid sintax\n", 23);
		return (-1);
	}
	expanded_line = add_char(expanded_line, line[i], i);
	if (!expanded_line)
		return (-1);
	return (i + 1);
}

char	*get_var(char *expanded_line, char *line, int var_pos, int len)
{
	char	**env;
	int		i;
	char	*var_name;

	i = -1;
	env = get_set_env(NULL);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		(NULL);
	var_name[len] = '\0';
	var_name[len - 1] = '=';
	while (++i < len - 1)
		var_name[i] = line[var_pos];
	while (env[i])
	{
		if(!ft_strncmp(var_name, env[i], len))
		{
			free(var_name);
			return (&env[i][len]);
		}
		i++;
	}
	free(var_name);
	return (NULL);
}

int	search_and_add_variable(char *expanded_line, char *line, int i)
{
	char	*expansion;
	int		j;

	expansion = NULL;
	j = i;
	while (is_space(line[i]) && line[i] != '\'' && line[i] != '"' \
			&& line[i] != '>' && line[i] != '<' && line[i] != '$')
		i++;
	expansion = get_var(expanded_line, line, dollar_pos + 1, (dollar_pos - i));
	if (!expansion)
	{
		free(expanded_line);
		return(-1);
	}
	refresh_line(line);
	return (i);
}

char	*expander(char *line)
{
	int		i;
	char	*expanded_line;

	i = 0;
	while (line[i])
	{
		if(str[i] == '\'')
			i = add_single_quote(expanded_line, line, i);
		else if (str[i] == '"')
			i = add_double_quote(expanded_line, line, i);
		else if(str[i] == '$')
			search_and_add_variable(line, i);
		else
			expanded_line = add_char(expanded_line, line[i], i);
		if (!expanded_line || i = -1)
		{
			free(line);
			exit(2);
		}
	}
	free(line);
	return (expanded_line);
}

'nao vai buscar variavel'
"vai buscar variavel"