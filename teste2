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
	int					used;

}	t_token;

typedef struct s_tree_node
{
	char 				*data;
	node_type 			type;
	struct s_tree_node *left;
	struct s_tree_node *right;

}	b_tree;

//parser.c
int			parser();

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

//expander.c
char		*get_var(char *line, int var_pos, int len);
char		*refresh_line(char *line, int x1, int x2, char *expansion);
char		*search_and_add_variable(char *line, int *i);
char		*expander(char *line);

//expander_utils.c
int			iter_single_quote(char *line, int i);
int			iter_double_quote(char **line, int i);

//tree_constructor.c
int			pipe_brancher(b_tree **tree, t_token **token);
int			redirection_checker(b_tree **tree, t_token **token);
int			token_setter(b_tree **tree, t_token **token);
int			tree_constructor(b_tree **tree, t_token **token);

//tree_constructor.c
int			set_token(b_tree **branch, t_token **token);
int			create_branch(b_tree **tree);
int    		redirect_to_last(b_tree *node, t_token **token, char *redir);
int			add_redirection(b_tree **branch, t_token **token, char *redir);

char		 **get_set_env(char **new_env);

#endif