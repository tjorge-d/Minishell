/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:36:37 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/03 15:00:18 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_to_expand(char *line, int i)
{
	while (!is_space(line[i]))
	{
		i--;
		if (i > 0 && line[i] == LESS && line[i - 1] == LESS)
			return (0);
	}
	while (is_space(line[i]))
	{
		i--;
		if (i > 0 && line[i] == LESS && line[i - 1] == LESS)
			return (0);
	}
	return (1);
}

char	*get_var(char *line, int var_pos, int len)
{
	char	**env;
	int		i;
	char	*var_name;

	i = -1;
	env = get_set_env(NULL, 0, 0);
	var_name = malloc(sizeof(char) * (len + 1));
	if (!var_name)
		return (free(line), fail_msg('M'), get_set_env(NULL, 1, 2), NULL);
	var_name[len] = '\0';
	var_name[len - 1] = '=';
	while (++i < len - 1)
		var_name[i] = line[var_pos + i];
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(var_name, env[i], len))
			return (free(var_name), &env[i][len]);
		i++;
	}
	free(var_name);
	return (NULL);
}

int	is_null_token(char *line, int i, char quote)
{
	if (line[i] == quote)
	{
		if (line[i + 1] == '|' || line[i + 1] == '<' \
		|| line[i + 1] == '>' || line[i + 1] == '\0' || is_space(line[i + 1]))
			return (1);
	}
	return (0);
}

int	iter_single_quote(char **line, int i)
{
	if (is_null_token((*line), i, '\''))
	{
		(*line)[i - 1] = NULL_TOKEN;
		(*line)[i] = ' ';
		return (i);
	}
	while ((*line)[i] && (*line)[i] != '\'')
		i++;
	if ((*line)[i] == '\0')
		return (fail_msg('S'), -1);
	(*line)[i] = SINGLE_Q;
	return (i + 1);
}

int	iter_double_quote(char **line, int i)
{
	if (is_null_token((*line), i, '"'))
	{
		(*line)[i - 1] = NULL_TOKEN;
		(*line)[i] = ' ';
		return (i);
	}
	while ((*line)[i] && (*line)[i] != '"')
	{
		if ((*line)[i] == '$' && (ft_isalnum((*line)[i + 1]) \
			|| (*line)[i + 1] == '?'))
			(*line) = search_and_add_variable(*line, &i);
		else
			i++;
	}
	if ((*line)[i] == '\0')
		return (fail_msg('S'), -1);
	(*line)[i] = DOUBLE_Q;
	return (i + 1);
}
