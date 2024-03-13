#include "../minishell.h"

int	set_token(b_tree **branch, t_token **token, int	token_type)
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
			iterator->right->type = token_type;
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

int	get_redirection_type(char *redir)
{
	if (!ft_strncmp(redir, "<", 2))
		return (REDIRECT_IN);
	if (!ft_strncmp(redir, ">", 2))
		return (REDIRECT_OUT);
	if (!ft_strncmp(redir, ">>", 3))
		return (REDIRECT_OUT_APP);
	return (0);
}

int	add_redirection(b_tree **branch, t_token **token, char *redir)
{
	b_tree	*iterator;
	int		redirection_type;
	
	iterator = *branch;
	redirection_type = get_redirection_type(redir);
	while (iterator)
	{
		if (iterator->right == NULL)
		{
			iterator->right = malloc(sizeof(b_tree));
			if (iterator->right == NULL)
				return (0);
			iterator->right->type = redirection_type;
			iterator->right->data = (*token)->next->data;
			(*token)->next->used = 1;
			(*token)->used = 1;
			iterator->right->left = NULL;
			iterator->right->right = NULL;
			return (1);
       	}
		iterator = iterator->right;
	}
	return (0);
}