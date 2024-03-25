#include "../minishell.h"

void	print_tokens(t_token **token)
{
	t_token	*test1;

	test1 = *token;
	printf("\ntokens:\n");
	while(test1)
	{
		printf("%s$\n",test1->data);
		test1 = test1->next;
	}
	printf("\n========================\n");
}

void	print_tree(b_tree **tree)
{
	b_tree	*test1;
	b_tree	*test2;
	test1 = *tree;
	test2 = *tree;
	printf("\ntree:\n");
	while(test2)
	{
		while(test1)
		{
			printf("%i", test1->type);
			if (test1->data && test1->data[0] == '\0')
				printf("(EMPTY TOKEN)");
			else if (test1->data && test1->data[0] == EMPTY)
				printf("(EMPTY EXPANSION)");
			else if (test1->data)
				printf("(%s)", test1->data);
			printf(" -> ");
			test1 = test1->right;
		}
		printf("\n");
		test2 = test2->left;
		test1 = test2;
	}
	printf("\n========================\n");
}

int	runner()
{
	b_tree	*tree;
	char 	*line;

	tree = NULL;
	line = readline("<Minishell> ");
	if (!line)
		return (free(line), 0);
	add_history(line);
	tree = parser(line);
	if (!tree)
		return (1);
	if (tree)
	{
		print_tree(&tree);
		destroy_tree(&tree);
	}
	return (1);
}

b_tree	*parser(char *line)
{
	t_token		*token;
	b_tree		*tree;
	char		*line_to_parse;

	token = NULL;
	tree = NULL;
	line_to_parse = expander(ft_strdup(line));
	free(line);
	if (!line_to_parse)
		return (NULL);
	if (!tokenizer(&token, &line_to_parse))
		return (free(line_to_parse), destroy_tokens(token, 'e'), NULL);
	free(line_to_parse);
	print_tokens(&token);
	if (!here_doc(&token))
		return (destroy_tokens(token, 'e'), NULL);
	if (!tree_constructor(&tree, &token))
		return (destroy_tokens(token, 'd'), destroy_tree(&tree), NULL);
	destroy_tokens(token, 'd');
	return (tree);
}

int main(int argc, char **argv ,char **envp)
{
	(void)argv;
	(void)argc;

	signal(SIGINT, exit_signal);
	signal(SIGQUIT, SIG_IGN);
	get_set_env(&envp, 0);
	while (runner())
		;
	rl_clear_history();
	get_set_env(NULL, 1);
	return (0);
}

//valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell