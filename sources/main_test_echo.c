#include "../minishell.h"

int main(int argc, char ** argv, char **envp)
{
	(void) argc;
	(void) argv;
	get_set_env(envp);
	printf("%s", getenv("HOME"));
}