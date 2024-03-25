#include "minishell.h"


void	close_fds(int **ans)
{
	int	i;

	i = 0;
	while (ans[i])
	{
		close(ans[i][0]);
		close(ans[i][1]);
		i ++;
	}
}

int	**create_pipes(int n_commands)
{
	int	i;
	int **ans;

	i = 0;
	ans = malloc(sizeof(int[2]) * (n_commands + 1));
	while (i < n_commands)
	{
		if(pipe(ans[i]))
		{
			close_fds(ans);
			free(ans);
			return (NULL);
		}
		i ++;
	}
	ans[i] = NULL;
	return (ans);
}