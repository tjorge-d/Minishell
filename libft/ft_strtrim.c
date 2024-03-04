/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:40 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:43:42 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ans;
	size_t	index_start;
	size_t	index_end;

	index_start = 0;
	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	while (s1[index_start] && ft_strchr(set, s1[index_start]))
		index_start++;
	index_end = ft_strlen(s1) - 1 ;
	while (s1[index_end] && ft_strchr(set, s1[index_end])
		&& index_end > index_start)
		index_end --;
	ans = ft_substr(s1, index_start, index_end - index_start + 1);
	return (ans);
}
/*
int main(void)
{
	printf("%s" , ft_strtrim("adasdav3dsadaad", "ad"));
}
*/