#include "../minishell.h"

int	count_args(b_tree *tree)
{
	int	i;

	i = 0;
	while(tree && (tree->type == COMMAND | tree->type == ARGUMENT))
	{
		i ++;
		tree = tree->right;
	}
	return (i);
}

void	run(char *command,char **args, int**pipes ,int command_n)
{
	dup2(pipes[command_n][1],STDIN_FILENO);
	dup2(pipes[command_n][0],STDOUT_FILENO);
	(void) pipes;
	(void) command_n;
	execve(command, args, get_set_env(NULL, 0));
	perror(command);
}