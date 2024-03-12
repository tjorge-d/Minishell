#include "../minishell.h"

int	set_token(b_tree **branch, t_token **token)
{
	b_tree *iterator;

	iterator = *branch;
	while (iterator)
	{

		if (iterator->right == NULL)
		{
			iterator->right = malloc(sizeof(b_tree));
			if (iterator->right == NULL)
				return (0);
			iterator->right->type = 42;
			iterator->right->data = (*token)->data;
			(*token)->used = 1;
			iterator->right->left = NULL;
			iterator->right->right = NULL;
			return (1);
		}
		iterator = iterator->right;
	}
	return (0);
}

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

int    redirect_to_last(b_tree *node, t_token **token, char *redir)
{
    node->right = malloc(sizeof(b_tree));
	if (node->right == NULL)
		return (0);
	if (redir[0] == '>')
		node->right->type = REDIRECT_OUT;
	if (redir[0] == '<')
		node->right->type = REDIRECT_IN;
	node->right->data = (*token)->next->data;
	(*token)->next->used = 1;
	(*token)->used = 1;
	node->right->left = NULL;
	node->right->right = NULL;
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
			(*token)->next->used = 1;
			(*token)->used = 1;
			return (1);
		}
		if (iterator->right == NULL)
		{
			if (!redirect_to_last(iterator, token, redir))
                return (0);
           return (1);
        }
		iterator = iterator->right;
	}
	return (0);
}