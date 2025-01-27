/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_constructor_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:47:23 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/11 16:45:49 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_tree	*init_node(char **data, int type)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (fail_msg('M'), NULL);
	if (!data)
		node->data = NULL;
	else
	{
		node->data = ft_strdup((*data));
		if (!node->data)
			return (free(node), fail_msg('M'), NULL);
	}
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int	set_token(t_tree **branch, t_token **token, int token_type)
{
	t_tree	*iterator;

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

int	create_branch(t_tree **tree)
{
	t_tree	*iterator;

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

int	add_redirection(t_tree **branch, t_token **token, char *redir)
{
	t_tree	*iterator;

	iterator = *branch;
	while (iterator)
	{
		if (iterator->right == NULL)
		{
			iterator->right = init_node(NULL, get_redirection_type(redir));
			if (iterator->right == NULL)
				return (0);
			if ((*token)->next == NULL || is_special((*token)->next->data[0]))
				return (fail_msg('S'), 2);
			if ((*token)->type == REDIRECT_IN_DOC)
				iterator->right->type = REDIRECT_IN_DOC;
			iterator->right->data = ft_strdup((*token)->next->data);
			if (!iterator->right->data)
				return (fail_msg('M'), 0);
			(*token)->next->used = 1;
			(*token)->used = 1;
			return (1);
		}
		iterator = iterator->right;
	}
	return (0);
}
