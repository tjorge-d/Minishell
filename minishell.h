#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <sys/types.h> 
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <signal.h>

extern int		global_var;

typedef enum special_chars
{
	GREATER = -7,
	LESS,
	V_BAR,
	SINGLE_Q,
	DOUBLE_Q,
	EMPTY,
	NULL_TOKEN,

}	special_chars;

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
	FLAGS,

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

typedef struct s_command
{
	int		fd_in;
	int		fd_out;
	char	*command;
	char	**args;
	pid_t	process_id;
} t_command;
//parser.c
b_tree		*parser(char *line);

//expander.c
char		*search_and_add_variable(char *line, int *i);
char		refiner(char c);
int			invalid_syntax(char *line);
char		*expander(char *line);

//expander_utils.c
int			is_to_expand(char *line, int i);
char		*refresh_line(char *line, int *x1, int x2, char *expansion);
char		*get_var(char *line, int var_pos, int len);
int			iter_single_quote(char **line, int i);
int			iter_double_quote(char **line, int i);

//tokenizer.c
void		destroy_tokens(t_token *token, char mode);
t_token		*token_creator(char *line, int x1, int x2);
int			add_token(char *line, t_token **token, int x1, int x2);
int 		tokenizer(t_token **head, char **line);

//tokenizer_utils.c
void 		iter_spaces(char *line, int *x, int *i);
char		*quote_remover(char *line, int x);
void		skip_quote(char **line, int *i, char quote);
int			iter_chars(t_token **head, char **line, int *x, int *i);

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

//here_doc.c
int			create_here_doc(char *exit_statement, t_token **token);
int			is_here_doc(t_token *prev_token);
int			invalid_here_doc_exit(t_token *curr_token);
int			here_doc(t_token **token);

//parser_utils.c
int			is_space(char c);
int			is_special(char c);
void 		free_matrix(char **matrix);

//signals.c
void		ctrl_c_signal_hd(int signal);
void		quit_here_doc(int signal);
void		ctrl_c_signal(int signal);

//get_data_path.c
int			is_built_in(char *line);
char		*check_command(char **path, char* data);
char		*get_data_path(char *data);


//utils_update
void		copy_array_2(char **src, char **dest);
void		print_array(char **arr);
char 		*search_var_value(char *var_name);
int			search_var_index(char *s);
int			array_len(char **arr);
char		**copy_array(char **src);
void		free_char_pp(char **array);
char		**get_set_env(char **new_env, int flag_to_free);

//echo.c
int			ft_echo(char **strs, int flag);
int			is_valid_flag(char *arg);
int			run_echo(char **args);

//pwd.c
int			print_pwd(void);

//free_utils.c
void		free_char_pp(char **array);

//built_in_exp.c
int			export(char *expression);
int			run_exp(char **args);

//cd_built_in.c
int			cd_without_args(void);
int			cd_with_arg(char *arg);
int			run_cd(char **args);

//unset.c
void	copy_array_skip(char **src, char **dest, int index);
int     run_unset(char **args);

//env.c
int     run_env(char **args);

//exit.c
int run_exit(t_command *cmd, int cmd_n, b_tree *tree, int flag);

//exec_utils2.c
int     count_args(b_tree *tree);
int     wait_loop(int n_commands,t_command *commands);
int     run_built_in(t_command *cmd, int cmd_n, b_tree *tree);
int     run_built_in_solo(b_tree *tree, t_command *cmd, char **args, int cmd_n);

//exec_utils.c
char ** build_args(b_tree *tree);
int     red_out_app(b_tree *tree, int *fd_out);
int     red_out(b_tree *tree, int *fd_out);
int     red_in_doc(b_tree *tree, int *fd_in);
int     red_in(b_tree *tree, int *fd_in);

//exec.c
void	run(t_command *commands ,int cmd_n, int total_cmds, b_tree *tree);
void	close_fds(t_command *coms, int total);
int		executor(b_tree *tree);
int     do_redirects(b_tree *tree, t_command *commands, int command_n);


#endif