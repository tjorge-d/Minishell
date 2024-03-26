#include "../minishell.h"

int	create_here_doc(char *exit)
{
	int		fd[2];
	char	*line;
	int		id;
	
	if (pipe(fd) == -1)
		return (write(2, "Error: failed to create a pipe\n", 32), 0);
	p_id = fork();
	if (p_id == -1)
		return (write(2, "Error: failed to create a fork\n", 32), 0);
	if(p_id == 0)
	{
		signal(SIGINT, exit_signal);
		line = readline("> ");
		if (!line)
			return (0);
		while(ft_strncmp(line, exit, ft_strlen(exit)) != 0 \
		|| ft_strlen(exit) != ft_strlen(line))
		{
			ft_putstr_fd(line, fd[1]);
			ft_putstr_fd("\n", fd[1]);
			free(line);
			line = readline("> ");
			if (!line)
				return (0);
		}
		signal(SIGINT, exit_signal);
		close(fd[0]);
		close(fd[1]);
		free(line);
	}
	free(exit);
	close(fd[1]);
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
			prev_token->data = mal			printf("entered run_child\n");
			printf("%s\n", args[0]);loc(sizeof(char) * 2);
			if (!prev_token->data)
				return (0);
			prev_token->data[0] = LESS;
			prev_token->data[1] = '\0';
			curr_token->data = ft_itoa(create_here_doc(curr_token->data));
			if (curr_token->data[0] == '0')
				return (0);
			prev_token->type = REDIRECT_IN_DOC;
		}
		prev_token = prev_token->next;
	}
	return (1);
}
