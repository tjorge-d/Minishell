#include "../minishell.h"

int	create_branch(b_tree **tree)
{
	b_tree *iterator;

	iterator = *tree;
	while (iterator)
	{
		if (iterator->left == NULL)
		{
			iterator->left = malloc(sizeof(b_tree));
			if (iterator->left == NULL)
				return (0);
			iterator->left->type = PIPE;
			iterator->left->data = NULL;
			iterator->left->left = NULL;
			iterator->left->right = NULL;
			return (1);
		}
		iterator = iterator->left;
	}
	return (0);
}
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
		}
		curr_token = curr_token->next;
	}
	return (1);
}

int	add_redirection(b_tree **branch, t_token **token, char *redir)
{
	b_tree *iterator;

	iterator = *branch;
	while (iterator)
	{
		if (iterator->type == REDIRECT_OUT && redir[0] == '>')
		{
			iterator->data = (*token)->next->data;
			return (1);
		}
		if (iterator->type == REDIRECT_IN && redir[0] == '<')
		{
			iterator->data = (*token)->next->data;
			return (1);
		}
		if (iterator->right == NULL)
		{
			iterator->right = malloc(sizeof(b_tree));
			if (iterator->right == NULL)
				return (0);
			if (redir[0] == '>')
				iterator->right->type = REDIRECT_OUT;
			if (redir[0] == '<')
				iterator->right->type = REDIRECT_IN;
			iterator->right->data = (*token)->next->data;
			iterator->right->left = NULL;
			iterator->right->right = NULL;
			return (1);
		}
		iterator = iterator->right;
	}
	return (0);
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
        if (!ft_strncmp(curr_token->data, redir, 2))
		{
			if (!add_redirection(&curr_branch, &curr_token, redir))
				return (0);	
		}
		//printf("DEBUG %s\n", redir);
		curr_token = curr_token->next;
		if (curr_token && !ft_strncmp(curr_token->data, "|", 2))
			curr_branch = curr_branch->left;
		if (curr_token == NULL && ft_strncmp(redir, "<", 2))
		{
		//	printf("DEBUG2\n");
			curr_token = *token;
			curr_branch = *tree;
			redir = "<";
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
	(*tree)->data = NULL;
	(*tree)->right = NULL;

	if (!pipe_brancher(tree, token))
		return (0);
	printf("\npipes:\n");
	test = *tree;
	while(test)
	{
		if (test->type == PIPE)
		 	printf("|\n");
		test = test->left;
	}
	if (!redirection_checker(tree, token))
		return (0);
	printf("\nredirections:\n");
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