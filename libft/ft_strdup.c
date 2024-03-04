/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:42:03 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:42:06 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	len;
	char	*ans;

	len = ft_strlen(s) + 1;
	ans = (char *)malloc((len) * sizeof(char));
	if (!ans)
		return (NULL);
	ft_strlcpy(ans, s, len);
	return (ans);
}
