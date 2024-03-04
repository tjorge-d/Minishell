/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prints.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:28:14 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/17 14:28:16 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_string(char *s)
{
	int	i;

	if (!s)
		return (ft_print_string("(null)"));
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return (i);
}

int	ft_printf_d(int n)
{
	return (ft_putnbr_base_signed(n, "0123456789"));
}

int	ft_printf_u(unsigned int n)
{
	return (ft_putnbr_base_unsigned(n, "0123456789"));
}

int	ft_printf_hex_x(unsigned int n)
{
	return (ft_putnbr_base_unsigned(n, "0123456789abcdef"));
}

int	ft_printf_hex_maj(unsigned int n)
{
	return (ft_putnbr_base_unsigned(n, "0123456789ABCDEF"));
}
