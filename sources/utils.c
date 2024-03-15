#include "../minishell.h"


void	copy_array_2(char **src, char **dest)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = strdup(src[i]);
		i ++;
	}
	dest[i] = NULL;
} 
