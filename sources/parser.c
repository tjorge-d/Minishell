#include "../minishell.h"

int	parser()
{
	char 		*line;
	t_token		*token;
	t_token		*test;

	token = NULL;
	line = readline(NULL);
	printf("\n");
	if(!tokenizer(&token, line))
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