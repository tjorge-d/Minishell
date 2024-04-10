/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:44:35 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/10 16:40:21 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	destroy_tokens(t_token *token, char mode)
{
	t_token	*temp;

	while (token)
	{
		if ((mode == 'e' || mode == 'h') && token->type == REDIRECT_IN_DOC)
			close(ft_atoi(token->next->data));
		if (token->data)
			free(token->data);
		temp = token;
		token = token->next;
		free(temp);
	}
	if (mode == 'e')
		write(2, "Error: Failed to create a token", 32);
}

t_token	*token_creator(char *line, int x1, int x2)
{
	t_token		*new_token;
	int			i;
	int			j;

	new_token = ft_calloc(1, sizeof(t_token));
	if (!new_token)
		return (free(line), NULL);
	new_token->data = ft_calloc((x2 - x1) + 2, sizeof(char));
	if (!new_token->data)
		return (free(new_token), free(line), NULL);
	i = 0;
	j = x1 -1;
	while (++j <= x2)
	{
		if (line[j] == NULL_TOKEN || (line[j] == EMPTY && x1 != x2))
			j++;
		if (j > x2)
			break ;
		new_token->data[i] = line[j];
		i++;
	}
	return (new_token);
}

int	add_token(char *line, t_token **token, int x1, int x2)
{
	t_token		*current;

	if (*token == NULL)
	{
		*token = token_creator(line, x1, x2);
		if (!token)
			return (get_set_env(NULL, 1, 2), 0);
		return (1);
	}
	current = *token;
	while (current->next != NULL)
		current = current->next;
	current->next = token_creator(line, x1, x2);
	if (!current->next)
		return (destroy_tokens(*token, 'e'), get_set_env(NULL, 1, 2), 0);
	return (1);
}

void	tokenizer(t_token **head, char **line)
{
	int		i;
	int		x[2];

	i = 0;
	x[0] = 0;
	x[1] = 0;
	(*head) = NULL;
	while ((*line)[i])
	{
		iter_spaces((*line), x, &i);
		iter_chars(head, line, x, &i);
		if (x[0] <= x[1] && (*line)[x[1]] != '\0')
			add_token((*line), head, x[0], x[1]);
	}
}
