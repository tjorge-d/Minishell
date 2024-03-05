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

typedef struct s_tree_node b_tree; 

struct b_tree
{
	char *data;
	node_type type;
	b_tree *left;
	b_tree *right;

};

char **get_set_env(char **new_env);
void ft_echo(char *str, int flag);
void free_char_pp(char **array);

#endif