#include "../minishell.h"

int	get_n_commands(b_tree *tree)
{
	int	ans;

	ans = 0;
	while (tree)
	{
		tree = tree->left;
		ans ++;
	}
	return (ans);
}

void create_pipes(int n_commands, t_command *commands)
{
	int	i;
	int pipes[2];

	i = 0;
	while (i < n_commands)
	{
		if (i == 0)
			commands[i].fd_in = 0;
		if (n_commands != 1)
		{
			pipe(pipes);
		}
		if(i == n_commands - 1)
			commands[i].fd_out = 1;
		else
		{
			commands[i].fd_out = pipes[1];
			commands[i+1].fd_in = pipes[0];
		}
		i ++;
	}
}
int do_redirects(b_tree *tree, t_command *commands, int command_n)
{
	while (tree && tree->type != PIPE)
		{
			if (tree->type == REDIRECT_IN)
			{
				if (red_in(tree, &commands[command_n].fd_in) == 0)
					return (0);
			}
			else if (tree->type == REDIRECT_IN_DOC)
				red_in_doc(tree, &commands[command_n].fd_in);
			else if (tree->type == REDIRECT_OUT)
			{
				if(!red_out(tree, &commands[command_n].fd_out))
					return (0);
			}
			else if (tree->type == REDIRECT_OUT_APP)
			{
				if(!red_out_app(tree, &commands[command_n].fd_out))
					return (0);
			}
			tree = tree->right;
		}
	return (1);
}
void	close_fds(t_command *coms, int total)
{
	int i;

	fprintf(stderr, "Total :%d\n\n", total);
	i = 0;
	while (i < total)
	{

		if(coms[i].fd_in != STDIN_FILENO)
			
			{
				fprintf(stderr,"closed FD_in %d\n",coms[i].fd_in);
				close(coms[i].fd_in);
			}
		if(coms[i].fd_out != STDOUT_FILENO)
			{
				fprintf(stderr,"closed FD_out %d\n",coms[i].fd_out);
				close(coms[i].fd_out);
			}
		i++;
	}
}
void do_child(b_tree *tree, int command_n ,t_command *commands, int total)
{
	int	i;

	i = 0; 
	if ((tree->type == PIPE || tree->type == FIRST_BRANCH))
	{
		tree = tree->right;
		if (!do_redirects(tree, commands, command_n))
		 	return ;
		while(tree && (tree->type !=COMMAND))
			tree = tree->right;
		if(tree)
			run(commands[command_n].command, commands, command_n, total);
		exit(112);
	}
}

void	fill_command(int n_cmd,t_command *commands, b_tree *tree)
{
	int i;

	i = 1;
	while (i < n_cmd)
	{
		tree = tree->left;
		i ++;
	}
	while (tree && tree->type != COMMAND)
	{
		tree = tree->right;
	}
	if (tree)
		commands[n_cmd].command = tree->data;
}
void	fill_commands(int n_commands,t_command *commands, b_tree *tree)
{
	int i;

	i = 0;
	while (i < n_commands)
	{
		fill_command(i, commands, tree);
		i++;
	}
}


int	executor(b_tree *tree)
{
	int	n_commands;
	t_command *commands;
	int	i;

	i = -1;
	n_commands = get_n_commands(tree);
	commands = malloc(sizeof(t_command) * n_commands);
	fill_commands(n_commands, commands, tree);
	create_pipes(n_commands, commands);
	if (n_commands == 1 && commands[0].command && is_built_in(commands[0].command))
		return (run_built_in(commands[0].command, build_args(tree)));
	while (++i < n_commands)
	{
		commands[i].args = build_args(tree);
		commands[i].process_id = fork();
		if (!commands[i].process_id)
			do_child(tree , i, commands, n_commands);
		else if (commands[i].process_id < 0)
			return (12);
		else
			tree = tree->left;
	}
	close_fds(commands,n_commands);
	wait_loop(n_commands, commands);
	return (i);
}
