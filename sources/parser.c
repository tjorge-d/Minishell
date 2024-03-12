#include "../minishell.h"

void	destroy_tree(b_tree **tree)
{
	b_tree		*curr_node;
	b_tree		*prev_node;
	b_tree		*next_branch;

	curr_node = *tree;
	prev_node = *tree;
	next_branch = curr_node->left;
	while (curr_node)
	{
		prev_node = curr_node;
		curr_node = curr_node->right;
		free(prev_node);
		if (curr_node == NULL)
		{
			if (next_branch == NULL)
				return ;
			curr_node = next_branch;
			next_branch = next_branch->left;
		}
	}
}

int	parser()
{
	char 		*line;
	t_token		*token;
	t_token		*teste;
	b_tree		*tree;

	token = NULL;
	tree = NULL;
	printf("line:\n");
	line = readline(NULL);
	line = expander(line);
	printf("\nexpanded line:\n%s\n\nTokens:\n", line);
	if(!tokenizer(&token, line))
		return (destroy_tokens(token, 'e'), 0);
	teste = token;
	while (teste)
	{
		printf("%s$\n", teste->data);
		teste = teste->next;
	}
	free(line);
	tree_constructor(&tree, &token);
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

	get_set_env(envp);
	if (!parser())
		return (2);
	return (0);
}

//valgrind --track-fds=yes --leak-check=full --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell