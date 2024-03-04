/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:43:30 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:43:32 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *) s;
	i = 0;
	while (str[i] != '\0')
		i++;
	if ((unsigned char) c == '\0')
		return (&str[i]);
	i--;
	while (i >= 0)
	{
		if (str[i] == (unsigned char) c)
			return (&str[i]);
		i--;
	}
	return (0);
}
