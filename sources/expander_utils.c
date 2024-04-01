#include "../minishell.h"

int	is_to_expand(char *line, int i)
{
	while(!is_space(line[i]))
	{
		i--;
		if (i > 0 && line[i] == LESS && line[i - 1] == LESS)
			return (0);
	}
	while(is_space(line[i]))
	{
		i--;
		if (i > 0 && line[i] == LESS && line[i - 1] == LESS)
			return (0);
	}
	return (1);
}

char	*refresh_line(char *line, int *x1, int x2, char *expansion)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc(sizeof(char) * ((ft_strlen(line) - (x2 - (*x1))) \
					+ (ft_strlen(expansion)) + 1));
	if (!new_line)
		return (free(line), free(expansion), \
		get_set_env(NULL, 1), failure_msg('M'), exit(0), NULL);
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
	free(line);
	return (new_line);
}

char	*get_var(char *line, int var_pos, int len)
{
	char	**env;
	int		i;
	char	*var_name;

	i = -1;
	env = get_set_env(NULL, 0);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (free(line), failure_msg('M'), exit(0), NULL);
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

int	is_null_token(char *line, int i, char quote)
{
	if (line[i] == quote)
	{
		if (line[i + 1] == '|' || line[i + 1] == '<' \
		|| line[i + 1] == '>' || line[i + 1] == '\0' || is_space(line[i + 1]))
				return (1);
	}
	return (0);
}

int	iter_single_quote(char **line, int i)
{
	if (is_null_token((*line), i, '\''))
	{
		(*line)[i - 1] = NULL_TOKEN;
		(*line)[i] = ' ';
		return (i);
	}
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if ((*line)[i] == '\0')
		return (failure_msg('S'), -1);
	(*line)[i] = SINGLE_Q;
	return (i + 1);
}

int	iter_double_quote(char **line, int i)
{
	if (is_null_token((*line), i, '"'))
	{
		(*line)[i - 1] = NULL_TOKEN;
		(*line)[i] = ' ';
		return (i);
	}
	while((*line)[i] && (*line)[i] != '"')
	{
		if((*line)[i] == '$')
			(*line) = search_and_add_variable(*line, &i);
		else
			i++;
	}
	if ((*line)[i] == '\0')
		return (failure_msg('S'), -1);
	(*line)[i] = DOUBLE_Q;
	return (i + 1);
}