#include "../minishell.h"

int	red_in(b_tree *tree, int *fd_in)
{
	int fd;

	fd = open(tree->data,O_RDONLY);
	if (fd == -1)
	{
		printf("ERROR COULD NOT OPEN OR FIND FILE :%s", tree->data);
		return (0);
	}
	else
	{
		if(*fd_in != STDIN_FILENO)
			close(*fd_in);
		*fd_in  = fd;
		return (1);
	}
}

int red_in_doc(b_tree *tree, int *fd_in)
{
	int	atoi;

	atoi = ft_atoi(tree->data);
	*fd_in = atoi;
	return (1);
}

int	red_out(b_tree *tree, int *fd_out)
{
	int fd;
	char *str;
	
	fd = open(tree->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		str = ft_strjoin("ERROR COULD NOT OPEN :", tree->data, 0, 0);
		ft_putstr_fd(str, 2);
		free(str);
		return (0);
	}
	else
	{
		if(*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out  = fd;
		return (1);
	}
}

int	red_out_app(b_tree *tree, int *fd_out)
{
	int fd;
	char *str;
	
	fd = open(tree->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{	
		str = ft_strjoin("ERROR COULD NOT OPEN :", tree->data, 0, 0);
		ft_putstr_fd(str, 2);
		free(str);
		return (0);
	}
	else
	{
		if(*fd_out != STDOUT_FILENO)
			close(*fd_out);
		*fd_out  = fd;
		return (1);
	}
}

char **build_args(b_tree *tree)
{
	char **args;
	int	i;

	i = 0;
	while (tree && (tree->type != COMMAND))
		tree = tree->right;
	if (tree)
	{
		args = malloc(sizeof(char *) *(count_args(tree) + 1));
		if(!args)
			return (NULL);
		while(tree && (tree->type == COMMAND || tree->type == ARGUMENT))
		{
			args[i++] = strdup(tree->data);
			tree = tree->right;
		}
		args[i] = NULL;
	}
	else
		return (NULL);
	return (args);
}
