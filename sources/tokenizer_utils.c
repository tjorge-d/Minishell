#include "../minishell.h"

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void iter_spaces(char *line, int *x, int *i)
{
	add_token
	while (is_space(line[(*i)]))
		(*i)++;
	x[0] = (*i);
}

int	iter_quote(char *line, int	*i, char quote, int *x2)
{
	while (line[(*i)])
	{
		(*i)++;
		if (line[(*i)] == quote)
		{
			(*x2) = (*i);
			return(1);
		}
	}
	return (0);
}

int	print_quotes(t_token **head, char *line, int *x, int *i)
{
	x[1] = (*i) - 1;
	if (x[0] <= x[1] && !add_token(line, head, x[0], x[1]))
		return (0);
	x[0] = (*i);
	if (!iter_quote(line, i, line[(*i)], &x[1]))
		return (0);
	if (!add_token(line, head, x[0], x[1]))
		return (0);
	x[0] = (*i) + 1;
	return (1);
}

int	iter_chars(t_token **head, char *line, int *x, int *i)
{
	while (!is_space(line[(*i)]) && line[(*i)])
	{
		if ( line[(*i)] == '|' || line[(*i)] == '<' || line[(*i)] == '>')
		{
			x[1] = (*i) - 1;
			if (x[0] <= x[1] && !add_token(line, head, x[0], x[1]))
				return (0);
			if (!add_token(line, head, *i, *i))
				return (0);
			x[0] = (*i) + 1;
		}
		else if (line[(*i)] == '"' || line[(*i)] == '\'')
		{
			//skip quotes
			if (!print_quotes(head, line, x, i))
				return (0);
		}
		(*i)++;
	}
	x[1] = (*i) - 1;
	return (1);
}