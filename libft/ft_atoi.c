/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <diogopaimsteam@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:35:26 by dcota-pa          #+#    #+#             */
/*   Updated: 2024/04/04 15:54:12 by dcota-pa         ###   ########.fr       */
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
	long		ans;
	int			signal;
	char		*s;

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

long	ft_exit_atoi(const char *str)
{
	long		ans;
	int			signal;
	char		*s;

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
	if (*s != '\0')
		return (LONG_MAX);
	return (ans);
}
