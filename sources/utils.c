#include "../minishell.h"

int	is_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'')
		return (1);
	return (0);
}

void free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while(matrix[++i])
		free(matrix[i]);
	free(matrix);
}

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
