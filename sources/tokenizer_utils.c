#include "../minishell.h"

int	is_special_token(char *line, int x1, int x2)
{
	if ((line[x1] == '<' && line[x2] == '<' &&  x1 == x2 - 1) \
		|| (line[x1] == '<' && line[x2] == '<' && x1 == x2) \
		|| (line[x1] == '>' && line[x2] == '>' &&  x1 == x2 - 1) \
		|| (line[x1] == '>' && line[x2] == '>' &&  x1 == x2) \
		|| (line[x1] == '|' && line[x2] == '|' &&  x1 == x2))
	{
		return (1);
	}
	else
		return (0);
}

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	iter_spaces(char *line, int *x, int *i)
{
	int	j;

	j = 0;
	if ((*i) > 0)
		j = (*i) - 1;
	while (is_space(line[(*i)]))
		(*i)++;
	x[0] = (*i);
	if (line[x[0]] == '|' && (x[0] == 0 || line[j] == '|' || j == 0))
		return (write(2, "Error: Invalid syntax\n", 23), 0);
	return (1);
}
char	*quote_remover(char *line, int x)
{
	int		i;
	char	*new_line;

	new_line = malloc(ft_strlen(line));
	if (!new_line)
		return (NULL);
	i = -1;
	while(++i < x)
		new_line[i] = line[i];
	while(line[i + 1])
	{
		new_line[i] = line[i + 1];
		i++;
	}
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

void	skip_quote(char **line, int *i, char quote)
{
	(*line) = quote_remover((*line), (*i));
	while ((*line)[(*i)])
	{
		if ((*line)[(*i)] == quote)
		{
			(*line) = quote_remover((*line), (*i));
			(*i)--;
			break ;
		}
		(*i)++;
	}
	return ;
}

int	iter_chars(t_token **head, char **line, int *x, int *i)
{
	while (!is_space((*line)[(*i)]) && (*line)[(*i)])
	{
		if ( (*line)[(*i)] == '|' || (*line)[(*i)] == '<' || (*line)[(*i)] == '>')
		{
			x[1] = (*i) - 1;
			if (x[0] <= x[1] && !add_token((*line), head, x[0], x[1]))
				return (0);
			x[0] = (*i);
			if ((*line)[(*i)] == '>' && (*line)[(*i) + 1] == '>')
				(*i)++;
			if ((*line)[(*i)] == '<' && (*line)[(*i) + 1] == '<')
				(*i)++;
			if (!add_token((*line), head, x[0], *i))
				return (0);
			x[0] = (*i) + 1;
		}
		else if ((*line)[(*i)] == '"' || (*line)[(*i)] == '\'')
			skip_quote(line, i, (*line)[(*i)]);
		(*i)++;
	}
	x[1] = (*i) - 1;
	return (1);
}