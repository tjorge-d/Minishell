#include "../minishell.h"

/*int	check_for_invalid_sintax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		if (!ft_strncmp(line[i], ">>>", 3) || !ft_strncmp(line[i], ">", 2) \
			|| !ft_strncmp(line[i], "<<<", 3) || !ft_strncmp(line[i], "<", 2))
	}
}*/

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
			(*line) = search_and_add_variable(*line, &i);
		else
			i++;
	}
	if ((*line)[i] == '\0')
	{
		write(2, "Error: Invalid sintax\n", 23);
		return (-1);
	}
	return (i + 1);
}