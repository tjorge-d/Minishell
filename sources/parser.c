#include "../minishell.h"

int	global_var;

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
	signal(SIGINT, ctrl_c_signal);
	line = readline("<Minishell> ");
	if (!line)
		return (printf("exit\n"), 0);
	if (line[0] == '\0')
		return (free(line), 1);
	add_history(line);
	tree = parser(line);
	if (!tree)
		return (1);
	if (tree)
	{
		global_var = executor(tree);
		destroy_tree(&tree);
	}
	return (1);
}

b_tree	*parser(char *line)
{
	t_token		*token;
	b_tree		*tree;
	char		*line_to_parse;

	line_to_parse = ft_strdup(line);
	free(line);
	line_to_parse = expander(line_to_parse);
	if (!line_to_parse)
		return (NULL);
	tokenizer(&token, &line_to_parse);
	free(line_to_parse);
	if (!here_doc(&token))
		return (destroy_tokens(token, 'h'), NULL);
	if (!tree_constructor(&tree, &token))
		return (destroy_tokens(token, 'h'), destroy_tree(&tree), NULL);
	destroy_tokens(token, 'd');
	return (tree);
}

int main(int argc, char **argv ,char **envp)
{
	(void)argv;
	(void)argc;

	global_var = 0;
	signal(SIGQUIT, SIG_IGN);
	get_set_env(envp, 0);
	increase_shell_lvl();
	while (runner())
		;
	rl_clear_history();
	get_set_env(NULL, 1);
	return (0);
}

//valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell