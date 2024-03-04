/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:35:26 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/03 15:51:35 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trim_str(char *str)
{
	while (*str == ' '
		|| *str == '\t'
		|| *str == '\n'
		|| *str == '\v'
		|| *str == '\f'
		|| *str == '\r')
		str++;
	return (str);
}

int	ft_atoi(const char *str)
{
	int		ans;
	int		signal;
	char	*s;

	ans = 0;
	s = trim_str((char *)str);
	signal = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			signal = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		if (signal == 1)
			ans = ans * 10 + (*s - '0');
		else
			ans = ans * 10 - (*s - '0');
		s++;
	}
	return (ans);
}
