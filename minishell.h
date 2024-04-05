/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:15:46 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/05 16:25:10 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <limits.h>
# include <sys/stat.h>

extern int		g_var;

typedef enum special_chars
{
	GREATER = -7,
	LESS,
	V_BAR,
	SINGLE_Q,
	DOUBLE_Q,
	EMPTY,
	NULL_TOKEN,
}	t_special_charss;

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
}	t_node_type;

typedef struct s_token
{
	char			*data;
	t_node_type		type;
	struct s_token	*next;
	int				used;
}	t_token;

typedef struct s_tree_node
{
	char				*data;
	t_node_type			type;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree;

typedef struct s_command
{
	int		fd_in;
	int		fd_out;
	char	*command;
	char	**args;
	pid_t	process_id;
	int		std_out;
	int		std_in;
}	t_cmd;
//parser.c
t_tree		*parser(char *line);

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
void		tokenizer(t_token **head, char **line);

//tokenizer_utils.c
void		iter_spaces(char *line, int *x, int *i);
char		*quote_remover(t_token **head, char *line, int x);
void		skip_quote(t_token **head, char **line, int *i, char quote);
void		iter_chars(t_token **head, char **line, int *x, int *i);

//tree_constructor.c
void		destroy_tree(t_tree **tree);
int			pipe_brancher(t_tree **tree, t_token **token);
int			redirection_checker(t_tree **tree, t_token **token);
int			command_builder(t_tree **tree, t_token **token);
int			tree_constructor(t_tree **tree, t_token **token);

//tree_constructor_utils.c
t_tree		*init_node(char **data, int type);
int			set_token(t_tree **branch, t_token **token, int token_type);
int			create_branch(t_tree **tree);
int			get_redirection_type(char *redir);
int			add_redirection(t_tree **branch, t_token **token, char *redir);

//here_doc.c
int			create_here_doc(char *exit_statement, t_token **token);
int			is_here_doc(t_token *prev_token);
int			invalid_here_doc_exit(t_token *curr_token);
int			here_doc(t_token **token);

//parser_utils.c
void		fail_msg(char mode);
int			is_space(char c);
int			is_special(char c);
void		free_matrix(char **matrix);

//signals.c
void		ctrl_c_signal_hd(int signal);
void		quit_here_doc(int signal);
void		ctrl_c_signal(int signal);

//get_data_path.c
int			is_built_in(char *line);
char		*check_command(char **path, char *data);
char		*get_data_path(char *data, t_tree **tree, t_token **token);

//utils_update
void		copy_array_2(char **src, char **dest);
char		*search_var_value(char *var_name);
int			search_var_index(char *s);
int			array_len(char **arr);
char		**copy_array(char **src);
char		**get_set_env(char **new_env, int flag_to_free, int flag_to_exit);

//echo.c
int			ft_echo(char **strs, int flag);
int			is_valid_flag(char *arg);
int			run_echo(char **args);

//pwd.c
int			print_pwd(void);

//free_utils.c
void		free_char_pp(char **array);
int			wait_loop(int n_commands, t_cmd *commands);
void		free_all(int n_commands, t_cmd *cmds, t_tree *tree, int rm_tree);

//built_in_exp.c
int			export(char *expression);
int			run_exp(char **args);

//cd_built_in.c
int			cd_without_args(void);
int			cd_with_arg(char *arg);
int			run_cd(char **args);

//unset.c
void		copy_array_skip(char **src, char **dest, int index);
int			run_unset(char **args);

//env.c
int			run_env(char **args);

//exit.c
int			run_exit(t_cmd *cmd, int cmd_n, t_tree *tree, int flag);
void		increase_shell_lvl(void);

//exec_utils3.c
int			ft_is_command(char *command);
void		close_fds(t_cmd *coms, int total);
void		fill_commands(int n_commands, t_cmd *commands, t_tree *tree);
void		fill_command(int n_cmd, t_cmd *commands, t_tree *tree);

//exec_utils2.c
int			count_args(t_tree *tree);
int			run_built_in(t_cmd *cmd, int cmd_n, t_tree *tree, int total_cmds);
int			run_built_in_solo(t_tree *tree, t_cmd *cmd, char **args, int cmd_n);

//exec_utils.c
int			build_args(int n_cmd, t_cmd *cmds, t_tree *tree);
int			red_out_app(t_tree *tree, int *fd_out);
int			red_out(t_tree *tree, int *fd_out);
int			red_in_doc(t_tree *tree, int *fd_in);
int			red_in(t_tree *tree, int *fd_in);

//exec.c
void		run(t_cmd *commands, int cmd_n, int total_cmds, t_tree *tree);
int			executor(t_tree *tree);
int			do_redirects(t_tree *tree, t_cmd *commands, int command_n);

//run_error.c
void		dir_err_handler(int t_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);
void		cmd_err_handler(int t_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);
void		fl_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);

#endif