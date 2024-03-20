#include "../minishell.h"

int	iter_single_quote(char *line, int i)
{
	while (line[i] && line[i] != '\'')
		i++;
	if (line[i] == '\0')
	{
		write(2, "Error: Invalid sintax\n", 23);
		return (-1);
	}
	return (i + 1);
}

int	iter_double_quote(char **line, int i)
{
	while((*line)[i] && (*line)[i] != '"')
	{
		if((*line)[i] == '$')
			(*line) = search_and_add_variable(*line, &i, 0);
		else
			i++;
	}
	if ((*line)[i] == '\0')
	{
		write(2, "Error: Invalid sintaaaaaax\n", 23);
		return (-1);
	}
	return (i + 1);
}