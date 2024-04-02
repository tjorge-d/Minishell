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
		if (prev_node->data)
			free(prev_node->data);
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

int	pipe_brancher(b_tree **tree, t_token **token)
{
    t_token		*curr_token;

	curr_token = *token;
	while (curr_token)
	{
        if (curr_token->data[0] == V_BAR)
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

	curr_token = *token;
	curr_branch = *tree;
	while (curr_token)
	{
        if (curr_token->data[0] == LESS || curr_token->data[0] == GREATER)
		{
			if (!add_redirection(&curr_branch, &curr_token, curr_token->data))
				return (0);	
		}
		curr_token = curr_token->next;
		if (curr_token && curr_token->data[0] == V_BAR)
			curr_branch = curr_branch->left;
	}
	return (1);
}

int	command_builder(b_tree **tree, t_token **token)
{
	t_token		*c_token;
	b_tree		*c_branch;
	int			token_type;

	c_token = *token;
	c_branch = *tree;
	token_type = COMMAND;
	while (c_token)
	{
		if (!c_token->used && c_token->data[0] != EMPTY)
		{
			if (token_type == COMMAND)
				c_token->data = get_data_path(c_token->data);
			if (!c_token->data || !set_token(&c_branch, &c_token, token_type))
				return (0);
			token_type = ARGUMENT;
		}
		if (c_token && c_token->data[0] == V_BAR)
		{
			c_branch = c_branch->left;
			token_type = COMMAND;
		}
		c_token = c_token->next;
	}
	return (1);
}

int	tree_constructor(b_tree **tree, t_token **token)
{
	*tree = NULL;
	*tree = init_node(NULL, FIRST_BRANCH);
	if (!tree)
		return (destroy_tokens((*token), 'h'), exit(0), 0);
	if (!pipe_brancher(tree, token))
		return (destroy_tree(tree), destroy_tokens((*token), 'h'), exit(0), 0);
	if (!redirection_checker(tree, token))
		return (destroy_tree(tree), destroy_tokens((*token), 'h'), exit(0), 0);
	if (!command_builder(tree, token))
		return (destroy_tree(tree), destroy_tokens((*token), 'h'), exit(0), 0);
	return(1);
}
