/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:32 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/08 18:36:08 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	i = 0;
	signal(SIGQUIT, SIG_IGN);
	while (i < n_commands)
	{
		waitpid(commands[i].process_id, &exit_status, 0);
		free_char_pp(commands[i].args);
		i++;
	}
	if (exit_status == 131)
		write(2, "Quit (core dumped)\n", 20);
	free(commands);
	return (WEXITSTATUS(exit_status));
}
