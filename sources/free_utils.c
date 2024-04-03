/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:32 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/03 12:26:33 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(int n_commands, t_cmd *commands, t_tree *tree)
{
	int	j;

	j = 0;
	while (j < n_commands)
	{
		if (commands[j].args)
			free_char_pp(commands[j].args);
		else 
			break ;
		j++;
	}
	close_fds(commands, n_commands);
	free(commands);
	destroy_tree (&tree);
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
	while (i < n_commands)
	{
		waitpid(commands[i].process_id, &exit_status, 0);
		free_char_pp(commands[i].args);
		i++;
	}
	free(commands);
	return (WEXITSTATUS(exit_status));
}
