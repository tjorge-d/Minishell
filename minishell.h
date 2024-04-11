/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 12:15:46 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/10 20:30:40 by tjorge-d         ###   ########.fr       */
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

//BUILT_INS
//cd_built_in.c
char		*get_error_msg_cd(char *arg);
void		ft_chdir_our_env(char *new_dir);
int			cd_without_args(void);
int			cd_with_arg(char *arg);
int			run_cd(char **args);

//echo_built_in.c
int			ft_echo(char **strs, int flag);
int			run_echo(char **args);
int			is_valid_flag(char *arg);
int			export(char *expression);
int			run_exp(char **args);

//env_built_in.c
int			has_equal(char *str);
int			print_env(void);
int			run_env(char **args);

//exit_built_in.c
int			run_exit(t_cmd *cmd, int cmd_n, t_tree *tree, int flag);

//exp_built_in.c
int			print_declare(void);
int			validate_expression(char *expression);
int			search_var_index(char *s);

//pwd_built_in.c
int			print_pwd(void);

//unset_built_in.c
void		copy_array_skip(char **src, char **dest, int index);
int			unset(char *expression);
int			run_unset(char **args);

//EXECUTOR
//commands.c
int			get_n_commands(t_tree *tree);
int			ft_is_command(char *command);
void		fill_command(int n_cmd, t_cmd *commands, t_tree *tree);
int			build_args(int cmd_n, t_cmd *commands, t_tree *tree);
void		fill_commands(int n_commands, t_cmd *commands, t_tree *tree);

//executor.c
int			create_pipes(int n_commands, t_cmd *commands, t_tree *tree);
int			do_child(t_tree *tree, int command_n, t_cmd *commands, int total);
int			executor(t_tree *tree);
void		close_fds(t_cmd *coms, int total);

//free_utils.c
void		free_all(int n_commands, t_cmd *cmds, t_tree *tree, int rm_tree);
void		free_char_pp(char **array);
int			wait_loop(int n_commands, t_cmd *commands);

//global_utils.c
char		*search_var_value(char *var_name);
void		copy_array_2(char **src, char **dest);
int			array_len(char **arr);
char		**copy_array(char **src);
char		**get_set_env(char **new_env, int flag_to_free, int flag_to_exit);

//main.c
void		increase_shell_lvl(void);
int			runner(void);
int			main(int argc, char **argv, char **envp);

//redirections.c
int			red_in(t_tree *tree, int *fd_in);
int			red_in_doc(t_tree *tree, int *fd_in);
int			red_out(t_tree *tree, int *fd_out);
int			red_out_app(t_tree *tree, int *fd_out);
int			do_redirects(t_tree *tree, t_cmd *commands, int command_n);

//run_errors.c
void		dir_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);
void		cmd_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);
void		fl_err_handler(int ttl_cmds, t_cmd *cmds, t_tree *tree, int cmd_n);
void		here_doc_ctrld_warn(char *str);

//run_utils.c
int			count_args(t_tree *tree);
void		run(t_cmd *cmds, int cmd_n, int total_cmds, t_tree *tree);
int			if_built_in_sequence(t_cmd *cmd, int cmd_n, t_tree *tree, int flag);
int			run_built_in_solo(t_tree *tree, t_cmd *cmd, char **args, int cmd_n);
int			run_built_in(t_cmd *cmd, int cmd_n, t_tree *tree, int total_cmds);

//signals.c
void		quit_here_doc(int signal);
void		ctrl_c_proccess(int signal);
void		ctrl_c_signal_hd(int signal);
void		ctrl_c_signal(int signal);

//PARSER
//expander_utils.c
int			is_to_expand(char *line, int i);
char		*get_var(char *line, int var_pos, int len);
int			is_null_token(char *line, int i, char quote);
int			iter_single_quote(char **line, int i);
int			iter_double_quote(char **line, int i);

//expander.c
char		*refresh_line(char *line, int *x1, int x2, char *expansion);
char		*search_and_add_variable(char *line, int *i);
char		refiner(char c);
int			invalid_syntax(char *line);
char		*expander(char *line);

//get_data_path.c
int			is_built_in(char *line);
char		*check_command(char **path, char *data);
char		*get_data_path(char *data, t_tree **tree, t_token **token);

//here_doc.c
void		here_doc_proccess(char *exit_str, t_token **token, int fd[2]);
int			create_here_doc(char *exit_statement, t_token **token);
int			is_here_doc(t_token *prev_token);
int			invalid_here_doc_exit(t_token *curr_token);
int			here_doc(t_token **token);

//parser_utils.c
int			is_space(char c);
int			is_special(char c);
void		free_matrix(char **matrix);
void		fail_msg(char mode);

//parser.c
void		print_tokens(t_token **token);
void		print_tree(t_tree **tree);
t_tree		*parser(char *line);

//tokenizer_utils.c
void		iter_spaces(char *line, int *x, int *i);
char		*quote_remover(t_token **head, char *line, int x);
void		skip_quote(t_token **head, char **line, int *i, char quote);
void		iter_chars(t_token **head, char **line, int *x, int *i);

//tokenizer.c
void		destroy_tokens(t_token *token, char mode);
t_token		*token_creator(char *line, int x1, int x2);
int			add_token(char *line, t_token **token, int x1, int x2);
void		tokenizer(t_token **head, char **line);
int			add_redirection(t_tree **branch, t_token **token, char *redir);

//tree_constructor_utils.c
t_tree		*init_node(char **data, int type);
int			set_token(t_tree **branch, t_token **token, int token_type);
int			create_branch(t_tree **tree);
int			get_redirection_type(char *redir);

//tree_constructor.c
void		destroy_tree(t_tree **tree);
int			pipe_brancher(t_tree **tree, t_token **token);
int			redirection_checker(t_tree **tree, t_token **token);
int			command_builder(t_tree **tree, t_token **token);
int			tree_constructor(t_tree **tree, t_token **token);

#endif
