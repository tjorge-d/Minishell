#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum node_type
{
	COMMAND,
	ARGUMENT,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE
}	node_type;

typedef struct tree_node
{
	char 				*data;
	node_type 			type;
	struct tree_node 	*left;
	struct tree_node 	*right;
}	b_tree;

#endif