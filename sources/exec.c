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

void	close_fds(int **ans)
{
	int	i;

	i = 0;
	while (ans[i])
	{
		close(ans[i][0]);
		close(ans[i][1]);
		i ++;
	}
}

int	**create_pipes(int n_commands)
{
	int	i;
	int **ans;

	i = 0;
	ans = malloc(sizeof(int[2]) * (n_commands + 1));
	while (i < n_commands)
	{
		if(pipe(ans[i]))
		{
			close_fds(ans);
			free(ans);
			return (NULL);
		}
		i ++;
	}
	ans[i] = NULL;
	return (ans);
}
int do_redirects(b_tree *tree, int **pipes, int command_n)
{
	while (tree->type == REDIRECT_IN || tree->type == REDIRECT_IN_DOC ||
				tree->type == REDIRECT_OUT || tree->type == REDIRECT_OUT)
		{
			if (tree->type == REDIRECT_IN)
			{
				if (red_in(tree, pipes[command_n]) == 0)
					return (0);
			}
			if (tree->type == REDIRECT_IN_DOC)
				red_in_doc(tree, pipes[command_n]);
			if (tree->type == REDIRECT_OUT)
			{
				if(!red_out(tree, pipes[command_n]))
					return (0);
			}
			if (tree->type == REDIRECT_OUT_APP)
			{
				if(!red_out_app(tree, pipes[command_n]))
					return (0);
			}
			tree = tree->right;
		}
	return (1);
}

void do_child(b_tree *tree, int command_n, int **pipes)
{
	int	i;
	char **args;

	i = 0; 
	while (i++ < command_n)
		tree = tree->left;
	if (tree->type == PIPE || tree->type == FIRST_BRANCH)
	{
		tree = tree->right;
		if (!do_redirects(tree, pipes, command_n))
			return ;
		args = build_args(tree);
		while(tree && (tree->type !=COMMAND))
			tree = tree->right;
		if(tree)
		{
			run(tree->data, args, pipes ,command_n);
		}
		close_fds(pipes);
	}
}

int	executor(b_tree *tree)
{
	int	n_commands;
	int	i;
	int	**pipes;
	int	fork_res;

	i = 0;
	n_commands = get_n_commands(tree);
	pipes = create_pipes(n_commands);
	while (i < n_commands)
	{
		fork_res = fork();
		if (!fork_res)
			do_child(tree , i, pipes);
		else if (fork_res < 0)
			return (12);
		else
			i ++;
	}
	printf("%d\n", i);
	return (i);
}
