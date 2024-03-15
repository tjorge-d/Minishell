#include "../minishell.h"

int	create_here_doc(char *exit)
{
	int		fd[2];
	char	*line;
	
	if (pipe(fd) == -1)
		return (write(2, "Error: a pipe failed to create\n", 32), 0);
	line = readline(NULL);
	if (!line)
		return (0);
	while(ft_strncmp(line, exit, ft_strlen(exit)) != 0 \
	|| ft_strlen(exit) != ft_strlen(line))
	{
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = readline(NULL);
		if (!line)
			return (0);
	}
	free(exit);
	free(line);
	close(fd[1]);
	return (fd[0]);
}

int	here_docker(t_token **token)
{
	t_token *prev_token;
	t_token *curr_token;

	curr_token = *token;
	prev_token = *token;
	while (curr_token)
	{
		curr_token = curr_token->next;
		if (!ft_strncmp(prev_token->data, "<<", 3) \
		&& curr_token && curr_token->data[0] != '|' \
		&& curr_token->data[0] != '>' && curr_token->data[0] != '<')
		{
			free(prev_token->data);
			prev_token->data = ft_strdup("<");
			if (!prev_token)
				return (0);
			curr_token->data = ft_itoa(create_here_doc(curr_token->data));
			if (curr_token->data[0] == '0')
				return (0);
			prev_token->type = REDIRECT_IN_DOC;
		}
	}
	return (1);
}
