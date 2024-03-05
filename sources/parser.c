#include "../minishell.h"

// b_tree	*parser(char *line)
// {
// 	b_tree	*head;
// 	b_tree	*tail;
// 	int		i;
// 	int		x1;
// 	int		x2;

// 	tail = head;
// 	x1 = 0;
// 	x2 = 0;
// 	i = -1;
// 	while (line[++i])
// 	{
// 		while (line[i] == ' ' && line[i])
// 			i++;
// 		x1 = i;
// 		while (line[i] != ' ' && line[i])
// 			i++;
// 		x2 = i - 1;
// 		if (x1 && x2)
// 		{
// 			tail->data = tokenizer(line, x1, x2);
// 			tail = tail->next;
// 			x1 = 0;
// 			x2 = 0;
// 		}
// 	}
// }

int	destroy_tokens(t_token *token)
{
	while (token)
	{
		free(token->data);
		token = token->next;
	}
	return (0);
}

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int add_token(char *line, t_token *token, int x1, int x2)
{
	int	i;

	token = malloc(sizeof(t_token));
	if (!token)
		return (0);
	token->next = malloc(sizeof(t_token));
	if (!token->next)
		return (0);
	token->data = malloc(sizeof(char) * (x2 - x1) + 2);
	if (!token->data)
		return (0);
	i = 0;
	while (x1 <= x2)
	{
		token->data[i] = line[x1];
		i++;
		x1++;
	}
	token->data[i] = '\0';
	token = token->next;
	return (1);
} 

int tokenizer(t_token *head, char *line, int x1, int x2)
{
	t_token		*tail;
	int			i;

	tail = head;
	i = 0;
	while (line[i])
	{
		while (is_space(line[i]))
			i++;
		x1 = i;
		while (!is_space(line[i]) && line[i])
			i++;
		x2 = i - 1;
		if (x1 <= x2 && !(x1 == 0 && x2 == 0))
		{
			if (!add_token(line, tail, x1, x2))
				return (destroy_tokens(head));
			x1 = 0;
			x2 = 0;
		}
	}
	tail = NULL;
	return (1);
}

int main()
{
	char 		*line;
	char 		**token;

	line = readline(NULL);
	if (!tokenizer(&token, line, 0, 0))
		return (1);
	while (token)
	{
		printf("%s\n", token->data);
		free(token->data);
		token = token->next;
	}
}

