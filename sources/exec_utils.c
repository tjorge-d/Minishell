#include "../minishell.h"

int	red_in(b_tree *tree, int *pipe)
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
		dup2(fd, pipe[1]);
		return (1);
	}
}

int red_in_doc(b_tree *tree, int *pipe)
{
	dup2(ft_atoi(tree->data), pipe[1]);
	return (1);
}

int	red_out(b_tree *tree, int *pipe)
{
	int fd;
	fd = open(tree->data, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("ERROR COULD NOT OPEN :%s", tree->data);
		return (0);
	}
	else
	{
		dup2(fd,pipe[0]);\
		//testar com close pipe[1];
		return(1);
	}
}

int	red_out_app(b_tree *tree, int *pipe)
{
	int fd;
	fd = open(tree->data, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		printf("ERROR COULD NOT OPEN :%s", tree->data);
		return (0);
	}
	else
	{
		dup2(fd,pipe[0]);
		return(1);
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
		while(tree && (tree->type == COMMAND | tree->type == ARGUMENT))
		{
			args[i++] = tree->data;
			tree = tree->right;
		}
		args[i] = NULL;
	}
	else
		return (NULL);
	return (args);
}
