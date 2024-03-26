#include "../minishell.h"

char	*search_and_add_variable(char *line, int *i)
{
	char		*expansion;
	char		empty_expansion[3];		
	int			j;

	empty_expansion[0]= DOUBLE_Q;
	empty_expansion[1]= DOUBLE_Q;
	empty_expansion[2]= '\0';
	j = (*i) + 1;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	expansion = ft_strdup(get_var(line, (*i) + 1, j - (*i)));
	if (!expansion)
		return(refresh_line(line, i, j, empty_expansion));
	return (refresh_line(line, i, j, expansion));
}

char	refiner(char c)
{
	if (c == '>')
		return (GREATER);
	else if (c == '<')
		return (LESS);
	else if (c == '|')
		return (V_BAR);
	else if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (c);
}

int	invalid_syntax(char *line)
{
	int 	i;

	i = 0;
	while(is_space(line[i]))
		i++;
	if(line[i] == V_BAR)
		return (write(2, "Error: Invalid syntax\n", 23), 1);
	while(line[i])
	{
		if (line[i] == V_BAR)
		{
			while(is_space(line[++i]))
				;
			if (line[i] == V_BAR || line[i] == '\0')
				return (write(2, "Error: Invalid syntax\n", 23), 1);
		}
		i++;
	}
	return (0);
}

char	*expander(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		line[i] = refiner(line[i]);
		if (line[i] == SINGLE_Q)
			i = iter_single_quote(line, i + 1);
		else if (line[i] == DOUBLE_Q)
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
	if (invalid_syntax(line))
		return (free(line), NULL);
	return (line);
}
