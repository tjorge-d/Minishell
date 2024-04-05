/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:53:14 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/05 12:34:30 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_var;

void	print_tokens(t_token **token)
{
	t_token	*test1;

	test1 = *token;
	printf("\ntokens:\n");
	while (test1)
	{
		printf("%s$\n", test1->data);
		test1 = test1->next;
	}
	printf("\n========================\n");
}

void	print_tree(t_tree **tree)
{
	t_tree	*test1;
	t_tree	*test2;

	test1 = *tree;
	test2 = *tree;
	printf("\ntree:\n");
	while (test2)
	{
		while (test1)
		{
			printf("%i", test1->type);
			if (test1->data && test1->data[0] == '\0')
				printf("(EMPTY TOKEN)");
			else if (test1->data && test1->data[0] == EMPTY)
				printf("(EMPTY EXPANSION)");
			else if (test1->data)
				printf("(%s)", test1->data);
			printf(" -> ");
			test1 = test1->right;
		}
		printf("\n");
		test2 = test2->left;
		test1 = test2;
	}
	printf("\n========================\n");
}

int	runner(void)
{
	t_tree	*tree;
	char	*line;

	tree = NULL;
	signal(SIGINT, ctrl_c_signal);
	line = readline("<Minishell> ");
	if (!line)
		return (printf("exit\n"), 0);
	if (line[0] == '\0')
		return (free(line), 1);
	add_history(line);
	tree = parser(line);
	if (!tree)
		return (1);
	if (tree)
	{
		g_var = executor(tree);
		destroy_tree(&tree);
	}
	return (1);
}

t_tree	*parser(char *line)
{
	t_token		*token;
	t_tree		*tree;
	char		*line_to_parse;

	line_to_parse = ft_strdup(line);
	free(line);
	line_to_parse = expander(line_to_parse);
	if (!line_to_parse)
		return (NULL);
	tokenizer(&token, &line_to_parse);
	free(line_to_parse);
	if (!here_doc(&token))
		return (destroy_tokens(token, 'h'), NULL);
	tree_constructor(&tree, &token);
	destroy_tokens(token, 'd');
	return (tree);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	(void)argc;
	g_var = 0;
	signal(SIGQUIT, SIG_IGN);
	get_set_env(envp, 0, 0);
	increase_shell_lvl();
	while (runner())
		;
	rl_clear_history();
	get_set_env(NULL, 1, 0);
	return (0);
}

// valgrind --track-fds=yes --leak-check=full 
// --show-leak-kinds=all  --suppressions=".valgrind.supp" ./minishell