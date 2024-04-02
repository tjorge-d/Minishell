#include "../minishell.h"

b_tree	*init_node(char **data, int type)
{
	b_tree	*node;

	node = malloc(sizeof(b_tree));
	if (!node)
		return (failure_msg('M'), NULL);
	if (!data)
		node->data = NULL;
	else
	{
		node->data = ft_strdup((*data));
		if (!node->data)
			return (free(node), failure_msg('M'), NULL);
	}
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	set_token(b_tree **branch, t_token **token, int	token_type)
{
	b_tree *iterator;

	iterator = *branch;
	while (iterator)
	{
		if (iterator->right == NULL)
		{
			iterator->right = init_node(&((*token)->data), token_type);
			if (iterator->right == NULL)
				return (0);
			(*token)->used = 1;
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
			iterator->left = init_node(NULL, PIPE);
			if (iterator->left == NULL)
				return (0);
			return (1);
		}
		iterator = iterator->left;
	}
	return (0);
}

int	get_redirection_type(char *redir)
{

	if (redir[0] == GREATER && redir[1] == GREATER)
		return (REDIRECT_OUT_APP);
	if (redir[0] == GREATER)
		return (REDIRECT_OUT);
	if (redir[0] == LESS)
		return (REDIRECT_IN);
	return (0);
}

int	add_redirection(b_tree **branch, t_token **token, char *redir)
{
	b_tree	*iterator;
	
	iterator = *branch;
	while (iterator)
	{
		if (iterator->right == NULL)
		{
			iterator->right = init_node(NULL, get_redirection_type(redir));
			if (iterator->right == NULL)
				return (0);
			if ((*token)->next == NULL || is_special((*token)->next->data[0]))
				return (failure_msg('S'), 0);
			if ((*token)->type == REDIRECT_IN_DOC)
				iterator->right->type = REDIRECT_IN_DOC;
			iterator->right->data = ft_strdup((*token)->next->data);
			if (!iterator->right->data)
				return (failure_msg('S'), 0);
			(*token)->next->used = 1;
			(*token)->used = 1;
			return (1);
       	}
		iterator = iterator->right;
	}
	return (0);
}
