#include "../minishell.h"

char	*get_var(char *line, int var_pos, int len)
{
	char	**env;
	int		i;
	char	*var_name;

	i = -1;
	env = get_set_env(NULL);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	var_name[len] = '\0';
	var_name[len - 1] = '=';
	while (++i < len - 1)
		var_name[i] = line[var_pos + i];
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

char	*refresh_line(char *line, int x1, int x2, char *expansion)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc(sizeof(char) * ((ft_strlen(line) - (x2 - x1)) \
					+ (ft_strlen(expansion)) + 1));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < x1)
		new_line[i] = line[i];
	j = 0;
	while (expansion[j])
		new_line[i++] = expansion[j++];
	j = x2;
	while(line[j])
		new_line[i++] = line[j++];
	new_line[i] = '\0';
	free (line);
	return (new_line);
}

char	*search_and_add_variable(char *line, int *i)
{
	char		*expansion;
	int			j;

	j = (*i) + 1;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	expansion = get_var(line, (*i) + 1, j - (*i));
	if (!expansion)
	{
		(*i) = j;
		return(line);
	}
	return (refresh_line(line, *i, j, expansion));
}

char	*expander(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if(line[i] == '\'')
			i = iter_single_quote(line, i + 1);
		else if (line[i] == '"')
			i = iter_double_quote(&line, i + 1);
		else if(line[i] == '$')
		{
			line = search_and_add_variable(line, &i);
			if (!line)
				return (NULL);
		}
		else
			i++;
		if (i == -1)
			return (free(line), NULL);
	}
	return (line);
}