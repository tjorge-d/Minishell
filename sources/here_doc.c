#include "../minishell.h"

void	here_doc_proccess(char *exit_statement, t_token **token, int fd[2])
{
	char	*line;

	signal(SIGINT, quit_here_doc);
	global_var = 0;
	line = readline("> ");
	while(line && (ft_strncmp(line, exit_statement, ft_strlen(exit_statement)) != 0 \
	|| ft_strlen(exit_statement) != ft_strlen(line)))
	{
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else if (!line && global_var == 0)
		printf("warning: here-document delimited by end-of-file (wanted `%s')\n", exit_statement);
	close(fd[1]);
	close(fd[0]);
	destroy_tokens((*token), 'h');
	get_set_env(NULL, 1);
	if (global_var == 2)
		exit(2);
	exit(0);
}

int	create_here_doc(char *exit_statement, t_token **token)
{
	int		fd[2];
	int		id;
	int		error_code;
	
	signal(SIGINT, ctrl_c_signal_hd);
	if (pipe(fd) == -1)
		return (write(2, "Error: failed to create a pipe\n", 32), 0);
	id = fork();
	if (id == 0)
		here_doc_proccess(exit_statement, token, fd);
	else
	{
		wait(&error_code);
		close(fd[1]);
		if (error_code != 0)
		{
			write(1, "> ^C\n", 6);
			close(fd[0]);
			return (0);
		}
	}
	return (fd[0]);
}

int	is_here_doc(t_token *prev_token)
{
	if (prev_token->data[0] == LESS && prev_token->data[1] == LESS)
		return (1);
	return (0);
}

int	invalid_here_doc_exit(t_token *curr_token)
{
	if(curr_token && (curr_token->data[0] == V_BAR \
		|| curr_token->data[0] == GREATER || curr_token->data[0] == LESS))
		return (1);
	return (0);
}

int	here_doc(t_token **token)
{
	t_token	*prev_token;
	t_token	*curr_token;

	prev_token = *token;
	while (prev_token)
	{
		curr_token = prev_token->next;
		if (is_here_doc(prev_token))
		{
			if (invalid_here_doc_exit(curr_token))
				return (write(2, "Error: Invalid syntax\n", 23), 0);
			free(prev_token->data);
			prev_token->data = malloc(sizeof(char) * 2);
			if (!prev_token->data)
				return (0);
			prev_token->data[0] = LESS;
			prev_token->data[1] = '\0';
			curr_token->data = ft_itoa(create_here_doc(curr_token->data, token));
			if (curr_token->data[0] == '0')
				return (1);
			prev_token->type = REDIRECT_IN_DOC;
		}
		prev_token = prev_token->next;
	}
	return (1);
}
