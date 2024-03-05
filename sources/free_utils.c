#include "../minishell.h"

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
		free(array);
	}
}