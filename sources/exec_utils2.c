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

void	run(char *command, t_command *commands ,int command_n, int total_cmds)
{
	printf("command -> %s\n",command);
	printf("command args-> %s\n",commands[command_n].args[0]);
	printf("command fd_in-> %d\n",commands[command_n].fd_in);
	printf("command fd_out-> %d\n\n",commands[command_n].fd_out);
	dup2(commands[command_n].fd_in,STDIN_FILENO);
	if(commands[command_n].fd_out != 1)
	{
		dup2(commands[command_n].fd_out,STDOUT_FILENO);
	}
	close_fds(commands, total_cmds);
	execve(command, commands[command_n].args, get_set_env(NULL, 0));
	perror(command);
}

int	wait_loop(int n_commands,t_command *commands)
{
	int i;
	int	exit_status;

	i = 0;
	while (i < n_commands)
	{
		waitpid(commands[i].process_id, &exit_status, 0);
		i++;
	}
	return (exit_status);
}