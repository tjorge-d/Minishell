#include "../minishell.h"

b_tree	*init_node()
{
	b_tree	*node;

	node = malloc(sizeof(b_tree));
	if (!node)
		return (NULL);
	node->data = NULL;
	node->type = 0;
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
			iterator->right = init_node();
			if (iterator->right == NULL)
				return (0);
			iterator->right->type = token_type;
			iterator->right->data = (*token)->data;
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
			iterator->left = init_node();
			if (iterator->left == NULL)
				return (0);
			iterator->left->type = PIPE;
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
			iterator->right = init_node();
			if (iterator->right == NULL)
				return (0);
			iterator->right->type = redirection_type;
			if ((*token)->next == NULL || (*token)->next->data[0] == '|' \
				|| (*token)->next->data[0] == '>' || (*token)->next->data[0] == '<')
				return (write(2, "Error: invalid syntax\n", 23), 0);
			iterator->right->data = (*token)->next->data;
			(*token)->next->used = 1;
			(*token)->used = 1;
			return (1);
       	}
		iterator = iterator->right;
	}
	return (0);
}