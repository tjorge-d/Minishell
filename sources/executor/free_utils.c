/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:32 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/18 17:17:03 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_all(int n_commands, t_cmd *cmds, t_tree *tree, int rm_tree)
{
	int	j;

	j = 0;
	while (j < n_commands)
	{
		if (cmds[j].args)
			free_char_pp(cmds[j].args);
		else 
			break ;
		j++;
	}
	close_fds(cmds, n_commands);
	free(cmds);
	if (rm_tree)
		destroy_tree(&tree);
	if (n_commands > 1)
		rl_clear_history();
}

void	free_char_pp(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			free(array[i]);
			i ++;
		}
	}
	free(array);
}

int	wait_loop(int n_commands, t_cmd *commands)
{
	int	i;
	int	exit_status;
	int	flag;

	i = 0;
	flag = 0;
	signal(SIGQUIT, SIG_IGN);
	while (i < n_commands)
	{
		waitpid(commands[i].process_id, &exit_status, 0);
		free_char_pp(commands[i].args);
		i++;
		if (exit_status == 2)
			flag = 1;
	}
	if (flag)
		write(1, "\n", 1);
	if (exit_status == 131)
		write(2, "Quit (core dumped)\n", 20);
	free(commands);
	return (WEXITSTATUS(exit_status));
}

void	close_fds(t_cmd *coms, int total)
{
	int	i;

	i = 0;
	while (i < total)
	{
		if (coms[i].fd_in != STDIN_FILENO)
			close(coms[i].fd_in);
		if (coms[i].fd_out != STDOUT_FILENO)
			close(coms[i].fd_out);
		i++;
	}
}
