/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:35:53 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:36:21 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n_members, size_t size)
{
	void	*ans;
	size_t	bytes_in_array;

	bytes_in_array = n_members * size;
	ans = malloc(bytes_in_array);
	if (!ans)
		return (NULL);
	ft_bzero(ans, bytes_in_array);
	return (ans);
}
