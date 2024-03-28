#include "../minishell.h"

int	print_pwd(void)
{
	printf("%s\n",getcwd(NULL, 0));
	return (0);
}