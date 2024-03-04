/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:38:56 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 14:38:58 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int	i;

	if (lst == NULL)
		return (NULL);
	i = 1;
	while (lst -> next != NULL)
	{
		lst = lst -> next;
		i++;
	}
	return (lst);
}
