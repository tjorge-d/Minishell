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

void	run(t_command *cmds ,int cmd_n, int total_cmds)
{
	fprintf(stderr,"FD _ IN =%d\n", cmds[cmd_n].fd_in);
	fprintf(stderr,"FD _ out =%d\n", cmds[cmd_n].fd_out);
	dup2(cmds[cmd_n].fd_in,STDIN_FILENO);
	if(cmds[cmd_n].fd_out != 1)
		dup2(cmds[cmd_n].fd_out,STDOUT_FILENO);
	close_fds(cmds, total_cmds);
	if(!is_built_in(cmds[cmd_n].command))
	{
		execve(cmds[cmd_n].command, cmds[cmd_n].args, get_set_env(NULL, 0));
		perror(cmds[cmd_n].command);
	}
	else 
		run_built_in(cmds[cmd_n].command, cmds, cmd_n);
	
}

int	wait_loop(int n_commands,t_command *commands)
{
	int i;
	int	exit_status;

	i = 0;
	while (i < n_commands)
	{
		waitpid(commands[i].process_id, &exit_status, 0);
		free_char_pp(commands[i].args);
		i++;
	}
	free(commands);
	return (exit_status);
}

int	run_built_in_solo(char *built_in, t_command *cmd, char **args, int cmd_n)
{
	int ans;

	cmd[cmd_n].args = args;
	ans = 2;
	if (!ft_strncmp(built_in, "echo", 5))
		ans = run_echo(cmd[cmd_n].args);
	else if (!ft_strncmp(built_in, "cd", 3))
	 	ans = run_cd(cmd[cmd_n].args);
	else if (!ft_strncmp(built_in, "pwd", 4))
		ans = print_pwd();
	else if (!ft_strncmp(built_in, "export", 8))
	 	ans = run_exp(cmd[cmd_n].args);
	// else if (!ft_strncmp(built_in, "unset", 6))
	// 	return (run_unset(args));
	// else if (!ft_strncmp(built_in, "env", 4))
	// 	return (run_env(args));
	// else if(!ft_strncmp(built_in, "exit", 5))
	// 	return (run_exit(args));
	free_char_pp(cmd[cmd_n].args);
	free(cmd);
	return (ans);
}
int	run_built_in(char *built_in, t_command *cmd, int cmd_n)
{
	int ans;

	ans = 2;
	if (!ft_strncmp(built_in, "echo", 5))
		ans = run_echo(cmd[cmd_n].args);
	else if (!ft_strncmp(built_in, "cd", 3))
	 	ans = run_cd(cmd[cmd_n].args);
	else if (!ft_strncmp(built_in, "pwd", 4))
		ans = print_pwd();
	else if (!ft_strncmp(built_in, "export", 8))
	 	ans = run_exp(cmd[cmd_n].args);
	// else if (!ft_strncmp(built_in, "unset", 6))
	// 	return (run_unset(args));
	// else if (!ft_strncmp(built_in, "env", 4))
	// 	return (run_env(args));
	// else if(!ft_strncmp(built_in, "exit", 5))
	// 	return (run_exit(args));
	return (ans);
}