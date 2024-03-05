#include "../minishell.h"

int main(int argc, char ** argv, char **envp)
{
	(void) argc;
	(void) argv;
	get_set_env(envp);
	ft_echo("'\"$PATH\"'", 1);
}