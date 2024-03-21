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
        if (!ft_strncmp(curr_token->data, "|", 2))
		{
			if (!create_branch(tree))
				return (0);
			curr_token->used = 1;
			if (curr_token->next == NULL)
				return (write(2, "Error: invalid syntax\n", 23), 0);
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
        if (curr_token->type == SPECIAL && !ft_strncmp(curr_token->data, redir, 1))
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
	t_token		*c_token;
	b_tree		*c_branch;
	int			token_type;

	c_token = *token;
	c_branch = *tree;
	token_type = COMMAND;
	while (c_token)
	{
		if (!c_token->used)
		{
			if (token_type == COMMAND)
				c_token->data = get_data_path(c_token->data);
			if (!c_token->data || !set_token(&c_branch, &c_token, token_type))
				return (0);
			token_type = ARGUMENT;
		}
		if (c_token && !ft_strncmp(c_token->data, "|", 2))
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
	*tree = init_node(NULL, FIRST_BRANCH);
	if (!tree)
		return (0);
	if (!pipe_brancher(tree, token))
		return (0);
	if (!redirection_checker(tree, token))
		return (0);
	if (!command_builder(tree, token))
		return (0);
	return(1);
}
