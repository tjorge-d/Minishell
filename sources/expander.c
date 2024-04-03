/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:37:03 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/03 14:00:06 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*refresh_line(char *line, int *x1, int x2, char *expansion)
{
	int		i;
	int		j;
	char	*new_line;

	new_line = malloc(sizeof(char) * ((ft_strlen(line) - (x2 - (*x1))) \
					+ (ft_strlen(expansion)) + 1));
	if (!new_line)
		return (free(line), free(expansion), fail_msg('M'), \
		get_set_env(NULL, 1, 2), NULL);
	i = -1;
	while (++i < (*x1))
		new_line[i] = line[i];
	j = 0;
	if (expansion)
	{
		while (expansion[j])
			new_line[i++] = expansion[j++];
	}
	(*x1) = i;
	j = x2;
	while (line[j])
		new_line[i++] = line[j++];
	new_line[i] = '\0';
	free(line);
	return (new_line);
}

char	*search_and_add_variable(char *line, int *i)
{
	char		*expansion;
	char		empty_expansion[2];		
	int			j;

	empty_expansion[0] = EMPTY;
	empty_expansion[1] = '\0';
	if (!is_to_expand(line, *i))
		return ((*i)++, line);
	j = (*i) + 1;
	if (line[(*i) + 1] == '?')
	{
		expansion = ft_itoa(g_var);
		if (!expansion)
			return (free(line), fail_msg('M'), get_set_env(NULL, 1, 2), NULL);
		return (refresh_line(line, i, *i + 2, expansion));
	}
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	expansion = get_var(line, (*i) + 1, j - (*i));
	if (!expansion)
		return (refresh_line(line, i, j, empty_expansion));
	expansion = ft_strdup(expansion);
	if (!expansion)
		return (free(line), get_set_env(NULL, 1, 2), NULL);
	return (refresh_line(line, i, j, expansion));
}

char	refiner(char c)
{
	if (c == '>')
		return (GREATER);
	else if (c == '<')
		return (LESS);
	else if (c == '|')
		return (V_BAR);
	else if (c == '\'')
		return (SINGLE_Q);
	else if (c == '"')
		return (DOUBLE_Q);
	else
		return (c);
}

int	invalid_syntax(char *line)
{
	int	i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (line[i] == V_BAR)
		return (fail_msg('S'), 1);
	while (line[i])
	{
		if (line[i] == V_BAR)
		{
			while (is_space(line[++i]))
				;
			if (line[i] == V_BAR || line[i] == '\0')
				return (fail_msg('S'), 1);
		}
		i++;
	}
	return (0);
}

char	*expander(char *line)
{
	int		i;

	i = 0;
	if (!line)
		return (fail_msg('M'), get_set_env(NULL, 1, 2), NULL);
	while (line[i])
	{
		line[i] = refiner(line[i]);
		if (line[i] == SINGLE_Q)
			i = iter_single_quote(&line, i + 1);
		else if (line[i] == DOUBLE_Q)
			i = iter_double_quote(&line, i + 1);
		else if (line[i] == '$')
			line = search_and_add_variable(line, &i);
		else
			i++;
		if (i == -1)
			return (free(line), NULL);
	}
	if (invalid_syntax(line))
		return (free(line), NULL);
	return (line);
}
