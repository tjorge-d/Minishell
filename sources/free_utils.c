#include "../minishell.h"

void	free_char_pp(char **array)
{
	int	i;

	i = 0;
	//printf("IN FREE %p\n", array);
	if (array && array[i])
	{
		while (array[i])
		{
			//fprintf(stderr,"freed string = %s\n\n",array[i]);
			free(array[i]);
			array[i] = NULL;
			i ++;
		}
	}
	free(array);
}
