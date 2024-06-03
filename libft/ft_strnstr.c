/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:21 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:43:23 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_l;
	size_t	j;
	char	*b;

	j = 0;
	b = (char *)big;
	len_l = ft_strlen(little);
	if (*little == 0)
		return ((char *) big);
	if (len == 0)
		return (0);
	while (b[j] && len_l <= len)
	{
		if (b[j] == *little && !ft_strncmp(&b[j], little, len_l))
			return (&b[j]);
		b++;
		len--;
	}
	return (NULL);
}
