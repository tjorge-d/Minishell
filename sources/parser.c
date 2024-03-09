#include "../minishell.h"

int	parser()
{
	char 		*line;
	t_token		*token;
	t_token		*test;

	token = NULL;
	printf("line:\n");
	line = readline(NULL);
	line = expander(line);
	printf("\nexpanded line:\n%s\n\nTokens:\n", line);
	if(!tokenizer(&token, line))
		return (destroy_tokens(token, 'e'), 0);
	test = token;
	while (test)
	{
		printf("%s$\n", test->data);
		test = test->next;
	}
	free(line);
	destroy_tokens(token, 'd');
	printf("========================\n");
	parser();
	return (1);
}

int main(int argc, char **argv ,char **envp)
{
	(void)argv;
	(void)argc;

	get_set_env(envp);
	if (!parser())
		return (2);
	return (0);
}