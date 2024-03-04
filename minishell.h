#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
typedef enum node_type
{
	COMMAND,
	ARGUMENT,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE
} node_type;

typedef struct tree_node
{
	char *data;
	node_type type;
	b_tree *left;
	b_tree *right;

} b_tree;

#endif