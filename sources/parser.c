#include "../minishell.h"

void	destroy_tokens(t_token *token)
{
	t_token *temp;

	while (token)
	{
		free(token->data);
		temp = token;
		token = token->next;
		free(temp);
	}
}

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
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

	if (*token == NULL)
	{
		*token = token_creator(line, x1, x2);
		if (!token)
			return (0);
		return (1);
	}
	current = *token;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = token_creator(line, x1, x2);
	if (!token)
			return (0);
	return (1);
}

int	go_to_quote(char *line, int	*i, char quote, int *x2)
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
	if (!go_to_quote(line, i, line[(*i)], &x[1]))
		return (0);
	printf ("x1= %i\nx2= %i\n\n", x[0], x[1]);
	if (!add_token(line, head, x[0], x[1]))
		return (0);
	(*i)++;
	x[0] = (*i);
	return (0);
}

int iter_spaces(t_token **head, char *line, int *x, int *i)
{
	while (is_space(line[(*i)]))
	{
		(*i)++;
		if (line[(*i)] == '"' || line[(*i)] == '\'')
		{
			x[0] = (*i);
			print_quotes(head, line, x, i);
		}
	}
	return (1);
}

int	iter_arg(t_token **head, char *line, int *x, int *i)
{
	while (!is_space(line[(*i)]) && line[(*i)])
	{
		if (line[(*i)] == '"' || line[(*i)] == '\'')
		{
			x[1] = (*i) - 1;
			printf ("x1= %i\nx2= %i\n\n", x[0], x[1]);
			if (!add_token(line, head, x[0], x[1]))
				return (0);
			x[0] = (*i);
			print_quotes(head, line, x, i);
		}
		(*i)++;
	}
	return (1);
}

int tokenizer(t_token **head, char *line, int i)
{
	int	x[2];

	x[0] = 0;
	x[1] = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			x[0] = i;
			print_quotes(head, line, x, &i);
		}
		iter_spaces(head, line, x, &i);
		x[0] = i;
		iter_arg(head, line, x, &i);
		x[1] = i - 1;
		printf("x2= %i!\n", x[1]);
		if (x[0] <= x[1] && !(line[i] == '"' || line[i] == '\'') && !is_space(line[x[1]]))
		{
			printf ("(1)\nx1= %i\nx2= %i\n\n", x[0], x[1]);
			if (!add_token(line, head, x[0], x[1]))
				return (0);
			x[0] = 0;
			x[1] = 0;
		}
	}
	return (1);
}

// int tokenizer(t_token **head, char *line, int x1, int x2)
// {
// 	int			i;

// 	i = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '"' || line[i] == '\'')
// 		{
// 			x1 = i;
// 			if (!go_to_quote(line, &i, line[i], &x2))
// 				return (0);
// 			printf("1\nx1= %d\nx2= %d\n\n",x1 ,x2);
// 			if (!add_token(line, head, x1, x2))
// 				return (0);
// 			i++;
// 			x1 = i;
// 		}
// 		while (is_space(line[i]))
// 		{
// 			i++;
// 			if (line[i] == '"' || line[i] == '\'')
// 			{
// 				x1 = i;
// 				if (!go_to_quote(line, &i, line[i], &x2))
// 					return (0);
// 				printf("2\nx1= %d\nx2= %d\n\n",x1 ,x2);
// 				if (!add_token(line, head, x1, x2))
// 					return (0);
// 				i++;
// 				x1 = i;
// 			}
// 		}
// 		x1 = i;
// 		while (!is_space(line[i]) && line[i])
// 		{
// 			if (line[i] == '"' || line[i] == '\'')
// 			{
// 				x2 = i - 1;
// 				printf("3\nx1= %d\nx2= %d\n\n",x1 ,x2);
// 				if (!add_token(line, head, x1, x2))
// 					return (0);
// 				x1 = i;
// 				if (!go_to_quote(line, &i, line[i], &x2))
// 					return (0);
// 				printf("4\nx1= %d\nx2= %d\n\n",x1 ,x2);
// 				if (!add_token(line, head, x1, x2))
// 					return (0);
// 				i++;
// 				x1 = i;
// 			}
// 			i++;
// 		}
// 		x2 = i - 1;
// 		if (x1 <= x2 && !(line[i] == '"' || line[i] == '\'') && !is_space(line[i]))
// 		{
// 			printf("5\nx1= %d\nx2= %d\n\n",x1 ,x2);
// 			if (!add_token(line, head, x1, x2))
// 				return (0);
// 			x1 = 0;
// 			x2 = 0;
// 		}
// 	}
// 	return (1);
// }

int	parser()
{
	char 		*line;
	t_token		*token;
	t_token		*test;

	token = NULL;
	line = readline(NULL);
	printf("\n");
	if(!tokenizer(&token, line, 0))
		return (destroy_tokens(token), 0);
	test = token;
	while (test)
	{
		printf("%s$\n", test->data);
		test = test->next;
	}
	free(line);
	destroy_tokens(token);
	printf("========================\n");
	parser();
	return (1);
}

int main()
{
	if (!parser())
		return (2);
	return (0);
}