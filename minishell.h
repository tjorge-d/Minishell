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
	REDIRECT_IN_DOC,
	REDIRECT_OUT,
	REDIRECT_OUT_APP,
	PIPE,
	FIRST_BRANCH,
	FLAGS
}	node_type;

typedef struct s_token
{

	char 					*data;
	node_type 				type;
	struct s_token			*next;
	int						used;

}	t_token;

typedef struct s_tree_node
{
	char 					*data;
	node_type 				type;
	struct s_tree_node 		*left;
	struct s_tree_node 		*right;

}	b_tree;

//parser.c
b_tree		*parser(char *line);

//expander.c
char		*get_var(char *line, int var_pos, int len);
char		*refresh_line(char *line, int x1, int x2, char *expansion);
char		*search_and_add_variable(char *line, int *i);
char		*expander(char *line);

//expander_utils.c
int			iter_single_quote(char *line, int i);
int			iter_double_quote(char **line, int i);

//tokenizer.c
void		destroy_tokens(t_token *token, char mode);
t_token		*token_creator(char *line, int x1, int x2);
int			add_token(char *line, t_token **token, int x1, int x2);
int 		tokenizer(t_token **head, char *line);

//tokenizer_utils.c
int			is_space(char c);
void 		iter_spaces(char *line, int *x, int *i);
void		skip_quote(char *line, int *i, char quote);
int			iter_chars(t_token **head, char *line, int *x, int *i);

//tree_constructor.c
void		destroy_tree(b_tree **tree);
int			pipe_brancher(b_tree **tree, t_token **token);
int			redirection_checker(b_tree **tree, t_token **token);
int			command_builder(b_tree **tree, t_token **token);
int			tree_constructor(b_tree **tree, t_token **token);

//tree_constructor_utils.c
b_tree		*init_node(char **data, int type);
int			set_token(b_tree **branch, t_token **token, int	token_type);
int			create_branch(b_tree **tree);
int			get_redirection_type(char *redir);
int			add_redirection(b_tree **branch, t_token **token, char *redir);

//get_data_path.c
int			is_built_in(char *line);
char		*check_command(char **path, char* data);
char		*get_data_path(char *data);

//here_docker.c
int			create_here_doc(char *exit);
int			here_docker(t_token **token);

//utils_update
char		**get_set_env(char ***new_env, int flag_to_free);
void		print_array(char **arr);
char 		*search_var_value(char *var_name);
int			search_var_index(char *s);
int			array_len(char **arr);
char		**copy_array(char **src);
void		free_char_pp(char **array);
char		**get_set_env(char ***new_env, int);

//echo.c
void		ft_echo(char **strs, int flag);

//free_utils.c
void		free_char_pp(char **array);

//utils.c
void		copy_array_2(char **src, char **dest);
int			array_len(char **arr);

//built_in_exp.c
int			export(char *expression);

//cd_built_in.c
void		cd_without_args(void);
void		cd_with_arg(char *arg);

//unset.c
void	copy_array_skip(char **src, char **dest, int index);

#endif