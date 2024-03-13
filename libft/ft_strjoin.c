/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:42:26 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:27 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2,int free_s1, int free_s2)
{
	size_t	size_1;
	size_t	size_2;
	char	*str;

	if (!s1 && !s2)
		return (ft_strdup(""));
	if (!s1 && s2)
		return (ft_strdup(s2));
	if (s1 && !s2)
		return (ft_strdup(s1));
	size_1 = ft_strlen(s1);
	size_2 = ft_strlen(s2);
	str = malloc (sizeof(char) * (size_1 + size_2 + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, size_1 + 1);
	ft_strlcat(str, s2, size_1 + size_2 + 1);
	if(free_s1)
		free(s1);
	if(free_s2)
		free(s2);
	return (str);
}
