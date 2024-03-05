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

typedef struct s_cd_contents cd_contents;

typedef struct s_cd_contents
{
	char *old_pwd;
	char *home;
	char *pwd;
} cd_contents;

char		**get_set_env(char **new_env);
cd_contents *get_set_cd_contents(cd_contents *newcd_cont);
int			set_env_old_pwd(char *new_old_pwd);
int			set_env_pwd(char *new_pwd);
void		ft_echo(char *str, int flag);
void		free_char_pp(char **array);

#endif