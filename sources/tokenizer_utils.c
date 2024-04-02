#include "../minishell.h"

void	iter_spaces(char *line, int *x, int *i)
{
	while (is_space(line[(*i)]))
		(*i)++;
	x[0] = (*i);
}

char	*quote_remover(t_token **head, char *line, int x)
{
	int		i;
	char	*new_line;

	new_line = malloc(ft_strlen(line));
	if (!new_line)
		return (free(line), destroy_tokens((*head), 'e'), \
			failure_msg('M'), exit(0), NULL);
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

void	skip_quote(t_token **head, char **line, int *i, char quote)
{
	(*line) = quote_remover(head, (*line), (*i));
	while ((*line)[(*i)])
	{
		if ((*line)[(*i)] == quote)
		{
			(*line) = quote_remover(head, (*line), (*i));
			(*i)--;
			break ;
		}
		(*i)++;
	}
	return ;
}

void	iter_chars(t_token **head, char **line, int *x, int *i)
{
	while (!is_space((*line)[(*i)]) && (*line)[(*i)])
	{
		if ( (*line)[(*i)] == V_BAR || (*line)[(*i)] == LESS || (*line)[(*i)] == GREATER)
		{
			x[1] = (*i) - 1;
			if (x[0] <= x[1])
				add_token((*line), head, x[0], x[1]);
			x[0] = (*i);
			if (((*line)[(*i)] == GREATER && (*line)[(*i) + 1] == GREATER) \
				|| ((*line)[(*i)] == LESS && (*line)[(*i) + 1] == LESS))
				(*i)++;
			add_token((*line), head, x[0], *i);
			x[0] = (*i) + 1;
		}
		else if ((*line)[(*i)] == DOUBLE_Q || (*line)[(*i)] == SINGLE_Q)
			skip_quote(head, line, i, (*line)[(*i)]);
		(*i)++;
	}
	x[1] = (*i) - 1;
}