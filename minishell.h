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
	PIPE,
	FLAGS
}	node_type;

typedef struct s_token
{
	char 				*data;
	struct s_token		*next;

}	t_token;

typedef struct s_tree_node
{
	char 				*data;
	node_type 			type;
	struct s_tree_node *left;
	struct s_tree_node *right;

}	b_tree;

char **get_set_env(char **new_env);
void ft_echo(char *str, int flag);
void free_char_pp(char **array);

#endif