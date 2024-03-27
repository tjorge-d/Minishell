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

void	run(char *command, t_command *cmds ,int cmd_n, int total_cmds)
{
	dup2(cmds[cmd_n].fd_in,STDIN_FILENO);
	if(cmds[cmd_n].fd_out != 1)
		dup2(cmds[cmd_n].fd_out,STDOUT_FILENO);
	close_fds(cmds, total_cmds);
	if(!is_built_in(cmds[cmd_n].command))
		execve(cmds[cmd_n].command, cmds[cmd_n].args, get_set_env(NULL, 0));
	else 
		run_built_in(cmds[cmd_n].command,cmds[cmd_n].args);
	perror(cmds[cmd_n].command);
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

int	run_built_in(char *built_in, char ** args)
{
	if (!ft_strncmp(built_in, "echo", 5))
		return (run_echo(args));
	else if (!ft_strncmp(built_in, "cd", 3))
		return (run_cd(args))
		|| !ft_strncmp(line, "pwd", 4) \
		|| !ft_strncmp(line, "export", 8) \
		|| !ft_strncmp(line, "unset", 6) \
		|| !ft_strncmp(line, "env", 4) \
		|| !ft_strncmp(line, "exit", 5))
		return (1);
	return (0);
}