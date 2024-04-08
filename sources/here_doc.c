/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:42:10 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/08 15:11:08 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	here_doc_proccess(char *exit_str, t_token **token, int fd[2])
{
	char	*line;

	signal(SIGINT, quit_here_doc);
	g_var = 0;
	line = readline("> ");
	while (line && (ft_strncmp(line, exit_str, ft_strlen(exit_str)) != 0 \
	|| ft_strlen(exit_str) != ft_strlen(line)))
	{
		ft_putstr_fd(line, fd[1]);
		ft_putstr_fd("\n", fd[1]);
		free(line);
		line = readline("> ");
	}
	if (line)
		free(line);
	else if (!line && g_var == 0)
		printf("warning: here-document delimited \
		by end-of-file (wanted `%s')\n", exit_str);
	close(fd[1]);
	close(fd[0]);
	destroy_tokens(*token, 'h');
	get_set_env(NULL, 1, 0);
	if (g_var == 130)
		exit(130);
	exit(0);
}

int	create_here_doc(char *exit_statement, t_token **token)
{
	int		fd[2];
	int		id;
	int		error_code;

	signal(SIGINT, ctrl_c_signal_hd);
	if (pipe(fd) == -1)
		return (fail_msg('P'), destroy_tokens((*token), 'h'), \
			get_set_env(NULL, 1, 2), 0);
	id = fork();
	if (id < 0)
		return (fail_msg('F'), destroy_tokens((*token), 'h'), \
			get_set_env(NULL, 1, 2), close(fd[0]), close(fd[1]), 0);
	if (id == 0)
		here_doc_proccess(exit_statement, token, fd);
	else
	{
		wait(&error_code);
		close(fd[1]);
		if (error_code != 0)
			return (write(1, "> ^C\n", 6), close(fd[0]), 0);
	}
	return (free(exit_statement), fd[0]);
}

int	is_here_doc(t_token *prev_token)
{
	if (prev_token->data[0] == LESS && prev_token->data[1] == LESS)
		return (1);
	return (0);
}

int	invalid_here_doc_exit(t_token *curr_token)
{
	if (curr_token && (curr_token->data[0] == V_BAR \
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
				return (fail_msg('S'), 0);
			prev_token->data[1] = '\0';
			curr_token->data = ft_itoa(\
			create_here_doc(curr_token->data, token));
			if (curr_token->data[0] == '0')
				return (0);
			prev_token->type = REDIRECT_IN_DOC;
		}
		prev_token = prev_token->next;
	}
	return (1);
}
