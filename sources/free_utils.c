#include "../minishell.h"

void free_all(int n_commands, t_command *commands, b_tree *tree)
{
	int	j;

	j = 0;
	while (j < n_commands)
	{	
		if (commands[j].args)
			free_char_pp(commands[j].args);
		else 
			break;
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
