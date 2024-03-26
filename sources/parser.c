#include "../minishell.h"

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
			if (test1->data)
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

void	runner()
{
	b_tree	*tree;
	char 	*line;

	tree = NULL;
	printf("line:\n");
	line = readline(NULL);
	//to think trough if there is no line (no history)
	add_history(line);
	tree = parser(line);
	free(line);
	if (tree)
	{
		print_tree(&tree);
		executor(tree);
		destroy_tree(&tree);
		runner();
	}
}

b_tree	*parser(char *line)
{
	t_token		*token;
	b_tree		*tree;

	token = NULL;
	tree = NULL;
	line = expander(line);
	printf("\nexpanded line:\n%s\n", line);
	if(!tokenizer(&token, line))
		return (destroy_tokens(token, 'e'), NULL);
	if(!here_docker(&token))
		return (destroy_tokens(token, 'e'), NULL);
	if(!tree_constructor(&tree, &token))
		return (destroy_tokens(token, 'd'), destroy_tree(&tree), NULL);
	destroy_tokens(token, 'd');
	return (tree);
}

int main(int argc, char **argv ,char **envp)
{
	(void)argv;
	(void)argc;

	get_set_env(&envp, 0);
	runner();

	rl_clear_history();
	get_set_env(NULL, 1);
	return (0);
}

//valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell