#include "../minishell.h"

void free_all(int n_commands, t_command *commands, b_tree *tree)
{
	int	j;

	j = 0;
	while (j < n_commands)
		{	
			if (commands[j].args)
				free_char_pp(commands[j++].args);
		}
	free(commands);
	get_set_env(NULL,1);
	destroy_tree (&tree);
}

void	free_char_pp(char **array)
{
	int	i;

	i = 0;
	if (array && array[i])
	{
		while (array[i])
		{
			free(array[i]);
			array[i] = NULL;
			i ++;
		}
	}
	free(array);
}
