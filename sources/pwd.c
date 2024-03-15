#include "../minishell.h"

int	print_pwd(void)
{
	printf(search_var_value("PWD"));
}