#include "../minishell.h"

int main(int argc, char ** argv, char **envp)
{
	(void) argc;
	get_set_env(envp);
	ft_echo(argv[1]);
}