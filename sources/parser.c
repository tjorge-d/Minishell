#include "../minishell.h"

int	parser()
{
	char 		*line;
	t_token		*token;
	b_tree		*tree;

	token = NULL;
	tree = NULL;
	printf("line:\n");
	line = readline(NULL);
	line = expander(line);
	printf("\nexpanded line:\n%s\n", line);
	if(!tokenizer(&token, line))
		return (free(line), destroy_tokens(token, 'e'), 0);
	free(line);
	if(!tree_constructor(&tree, &token))
		return (destroy_tokens(token, 'd'), destroy_tree(&tree), 0);
	destroy_tokens(token, 'd');
	destroy_tree(&tree);
	printf("========================\n");
	parser();
	return (1);
}

int main(int argc, char **argv ,char **envp)
{
	(void)argv;
	(void)argc;

	get_set_env(&envp, 0);
	if (!parser())
		return (2);
	get_set_env(NULL, 1);
	return (0);
}

//valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell