/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:41:43 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:41:46 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	str_counter(char const *str, char c)
{
	size_t	i;
	size_t	n_strs;

	i = 0;
	n_strs = 0;
	while (str[i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
			n_strs ++;
		while (str[i] && str[i] != c)
			i++;
	}
	return (n_strs);
}

static char	**free_arrays(char **arrs, size_t n_arr)
{
	size_t	i;

	i = 0;
	while (i < n_arr)
	{
		free(arrs[i]);
		i++;
	}
	free (arrs);
	return (NULL);
}

static char	**fill_arrays(char const *s, char c, size_t n_strs, char **arrays)
{
	char	*str;
	size_t	n_s;
	size_t	index;
	size_t	counter;

	n_s = 0;
	index = 0;
	while (n_s < n_strs)
	{
		counter = 0;
		while (s[index] == c)
			index++;
		while (s[index] && s[index] != c)
		{
			counter++;
			index++;
		}
		str = ft_substr(s, index - counter, counter);
		if (str == NULL)
			return (free_arrays(arrays, n_s));
		arrays[n_s] = str;
		n_s ++;
	}
	arrays[n_s] = NULL;
	return (arrays);
}

char	**ft_split(char const *s, char c)
{
	char	**ans;
	size_t	n_strs;

	if (!s)
		return (NULL);
	n_strs = str_counter(s, c);
	ans = (char **)malloc(sizeof(char *) * (n_strs + 1));
	if (!ans)
		return (NULL);
	return (fill_arrays(s, c, n_strs, ans));
}
/*
int main() {

	char *string = "  umapalavra    ";
	char **result = ft_split(string, ' ');
	int i = 0;
	while (result[i] != NULL)
	{
		printf("$%s$\n", result[i]);
		i++;
	}

  return 0;
}
*/
