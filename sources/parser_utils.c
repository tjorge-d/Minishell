#include "../minishell.h"

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == GREATER || c == LESS || c == V_BAR)
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