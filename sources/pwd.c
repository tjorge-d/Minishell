#include "../minishell.h"

void	print_pwd(void)
{
	printf("%s\n",getcwd(NULL, 0));
}