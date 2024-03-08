#include "../minishell.h"

void	destroy_tokens(t_token *token, char mode)
{
	t_token *temp;

	while (token)
	{
		free(token->data);
		temp = token;
		token = token->next;
		free(temp);
	}
	if (mode == 'e')
		write(2, "Error: A token had a problem being created", 43);
}

t_token	*token_creator(char *line, int x1, int x2)
{
	t_token		*new_token;
	int			i;
	i = 0;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->data = malloc(sizeof(char) * (x2 - x1) + 2);
	if (!new_token->data)
		return (free(new_token), NULL);
	while (x1 <= x2)
	{
		new_token->data[i] = line[x1];
		i++;
		x1++;
	}
	new_token->data[i] = '\0';
	new_token->next = NULL;	
	return (new_token);
}

int	add_token(char *line, t_token **token, int x1, int x2)
{
	t_token		*current;

	//printf ("x1= %i\nx2= %i\n\n", x[0], x[1]);
	if (*token == NULL)
	{
		*token = token_creator(line, x1, x2);
		if (!token)
			return (0);
		return (1);
	}
	current = *token;
	while (current->next != NULL)
		current = current->next;
	current->next = token_creator(line, x1, x2);
	if (!token)
			return (0);
	return (1);
}

int tokenizer(t_token **head, char *line)
{
	int		i;
	int		x[2];

	i = 0;
	x[0] = 0;
	x[1] = 0;
	while (line[i])
	{
		iter_spaces(line, x, &i);
		if (!iter_chars(head, line, x, &i))
			return(0);
		if (x[0] <= x[1] && line[x[1]] != '\0' && !is_space(line[x[1]]))
		{
			if (!add_token(line, head, x[0], x[1]))
				return (0);
		}
	}
	return (1);
}