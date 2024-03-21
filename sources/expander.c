#include "../minishell.h"

char	*get_var(char *line, int var_pos, int len)
{
	char	**env;
	int		i;
	char	*var_name;

	i = -1;
	env = get_set_env(NULL, 0);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (NULL);
	var_name[len] = '\0';
	var_name[len - 1] = '=';
	while (++i < len - 1)
		var_name[i] = line[var_pos + i];
	i = 0;
	while (env[i])
	{
		if(!ft_strncmp(var_name, env[i], len))
			return (free(var_name), &env[i][len]);
		i++;
	}
	free(var_name);
	return (NULL);
}

char	*refresh_line(char *line, int *x1, int x2, char *expansion)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc(sizeof(char) * ((ft_strlen(line) - (x2 - (*x1))) \
					+ (ft_strlen(expansion)) + 1));
	if (!new_line)
		return (NULL);
	i = -1;
	while (++i < (*x1))
		new_line[i] = line[i];
	j = 0;
	if (expansion)
	{
		while (expansion[j])
			new_line[i++] = expansion[j++];
	}
	(*x1) = i;
	j = x2;
	while(line[j])
		new_line[i++] = line[j++];
	new_line[i] = '\0';
	free (line);
	return (new_line);
}


char	*capsulate_special_characters(char *expansion, int *special_pos, char quote)
{
	int		i;
	char	*new_expansion;

	new_expansion = malloc(sizeof(char) * ft_strlen(expansion) + 3);
	if(!new_expansion)
		return (free(expansion), NULL);
	i = -1;
	while (++i < (*special_pos))
		new_expansion[i] = expansion[i];
	new_expansion[i++] = quote;
	new_expansion[i++] = expansion[(*special_pos)];
	new_expansion[i++] = quote;
	while (expansion[i - 2])
	{
		new_expansion[i] = expansion[i - 2];
		i++;
	}
	(*special_pos) +=2;
	new_expansion[i] = '\0';
	free(expansion);
	return (new_expansion);
}

char	*capsulate_double_quote(char *expansion, int *special_pos)
{
	int		i;
	char	*new_expansion;

	new_expansion = malloc(sizeof(char) * ft_strlen(expansion) + 5);
	if(!new_expansion)
		return (free(expansion), NULL);
	i = -1;
	while (++i < (*special_pos))
		new_expansion[i] = expansion[i];
	new_expansion[i++] = '"';
	new_expansion[i++] = '\'';
	new_expansion[i++] = expansion[(*special_pos)];
	new_expansion[i++] = '\'';
	new_expansion[i++] = '"';
	while (expansion[i - 4])
	{
		new_expansion[i] = expansion[i - 4];
		i++;
	}
	(*special_pos) +=4;
	new_expansion[i] = '\0';
	free(expansion);
	return (new_expansion);
}

char	*expansion_handler(char *expansion, int outside_quotes)
{
	int		i;
	char	*new_expansion;

	new_expansion = ft_strdup(expansion);
	free(expansion);
	if (!new_expansion)
		return (NULL);
	i = -1;
	while (new_expansion[++i])
	{
		if (is_special(new_expansion[i]) && outside_quotes)
			new_expansion = capsulate_special_characters(new_expansion, &i, '"');
		else if (new_expansion[i] == '"' && outside_quotes)
			new_expansion = capsulate_special_characters(new_expansion, &i, '\'');
		else if (new_expansion[i] == '"' && !outside_quotes)
			new_expansion = capsulate_double_quote(new_expansion, &i);
		if (!new_expansion)
			return (NULL);
	}
	return (new_expansion);
}

char	*search_and_add_variable(char *line, int *i, int outside_quotes)
{
	char		*expansion;
	int			j;

	j = (*i) + 1;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	expansion = ft_strdup(get_var(line, (*i) + 1, j - (*i)));
	if (!expansion)
		return(refresh_line(line, i, j, NULL));
	expansion = expansion_handler(expansion, outside_quotes);
	if (!expansion)
		return (NULL);
	return (refresh_line(line, i, j, expansion));
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
			line = search_and_add_variable(line, &i, 1);
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

int	expand_tokens(t_token **token)
{
	t_token *iterator;

	iterator = *token;
	while (iterator)
	{
		iterator->data = expander(iterator->data);
		if (!iterator->data)
			return (0);
		iterator = iterator->next;
	}
	return (1);
}
