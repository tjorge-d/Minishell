#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <errno.h>

typedef enum node_type
{
	COMMAND,
	ARGUMENT,
	REDIRECT_IN,
	REDIRECT_OUT,
	PIPE	
}	node_type;

typedef struct s_tree_node
{
	char *data;
	node_type type;
	struct s_tree_node *left;
	struct s_tree_node *right;

}	b_tree;


char		**get_set_env(char ***new_env, int flag_to_free);
int			set_env_old_pwd(char *new_old_pwd);
int			set_env_pwd(char *new_pwd);
void		ft_echo(char *str, int flag);
void		free_char_pp(char **array);
char		*get_var_from_env(char *var, int len);
char		**copy_array(char **src);
void		copy_array_2(char **src, char **dest);
int			export(char *expression);
int			array_len(char **arr);
void		print_array(char **arr);
void		ft_free(void **ptr);
int			search_var_index(char *s);
char		*search_var_value(char *var_name);
void		cd_without_args(void);
void		cd_with_arg(char *arg);

#endif