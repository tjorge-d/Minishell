#include "../minishell.h"

void	ft_echo(char **strs, int flag)
{
	int	i;

	i = 0;
	if(!strs)
		return ;
	while(strs[i])
	{
		ft_putstr_fd(strs[i],STDOUT_FILENO);
		i++;
	}
	if (!flag)
		write(1, "\n", 1);
	exit(0);
}
