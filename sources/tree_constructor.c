#include "../minishell.h"

int	pipe_brancher(b_tree **tree, t_token **token)
{
    t_token		*curr_token;

	curr_token = *token;
	while (curr_token)
	{
        if (!ft_strncmp(curr_token->data, "|", 2))
		{
			if (!create_branch(tree))
				return (0);
			curr_token->used = 1;
		}
		curr_token = curr_token->next;
	}
	return (1);
}

int	redirection_checker(b_tree **tree, t_token **token)
{
	t_token		*curr_token;
	b_tree		*curr_branch;
	char		*redir;

	redir = ">";
	curr_token = *token;
	curr_branch = *tree;
	while (curr_token)
	{
        if (!ft_strncmp(curr_token->data, redir, 1))
		{
			if (!add_redirection(&curr_branch, &curr_token, curr_token->data))
				return (0);	
		}
		curr_token = curr_token->next;
		if (curr_token && !ft_strncmp(curr_token->data, "|", 2))
			curr_branch = curr_branch->left;
		if (curr_token == NULL && ft_strncmp(redir, "<", 1))
		{
			curr_token = *token;
			curr_branch = *tree;
			redir = "<";
		}
	}
	return (1);
}

int	command_builder(b_tree **tree, t_token **token)
{
	t_token		*curr_token;
	b_tree		*curr_branch;
	int			token_type;

	curr_token = *token;
	curr_branch = *tree;
	token_type = COMMAND;
	while (curr_token)
	{
		if (!curr_token->used)
		{
			if (!set_token(&curr_branch, &curr_token, token_type))
				return (0);
			token_type = ARGUMENT;
		}
		curr_token = curr_token->next;
		if (curr_token && !ft_strncmp(curr_token->data, "|", 2))
		{
			curr_branch = curr_branch->left;
			token_type = COMMAND;
		}
	}
	return (1);
}

int	tree_constructor(b_tree **tree, t_token **token)
{
	b_tree	*test;
	b_tree	*test2;

	*tree = malloc(sizeof(b_tree));
	(*tree)->left = NULL;
	(*tree)->right = NULL;
	(*tree)->type = FIRST_BRANCH;
	(*tree)->data = NULL;

	if (!pipe_brancher(tree, token))
		return (0);
	if (!redirection_checker(tree, token))
		return (0);
	if (!command_builder(tree, token))
		return (0);
	printf("\ncomplete tree:\n");
	test = *tree;
	test2 = *tree;
	while(test2)
	{
		while(test)
		{
			printf("%i", test->type);
			if (test->data)
				printf("(%s)", test->data);
			printf("->");
			test = test->right;
		}
		printf("\n");
		test2 = test2->left;
		test = test2;
	}
	printf("\n");
	return(1);
}