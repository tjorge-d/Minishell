/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnbr_bases.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:27:59 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/17 14:28:02 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	base_length(char *base)
{
	int	i;

	i = 0;
	while (base[i] != '\0')
	{
		i++;
	}
	return (i);
}

static void	print_nbr_in_base(unsigned long nbr, char *base, 
	int *counter_of_print, int is_last)
{
	char			char_to_print;
	unsigned int	b_size;

	b_size = base_length(base);
	if (is_last == 1)
	{
		return ;
	}
	if (nbr / b_size == 0)
	{
		print_nbr_in_base(nbr / b_size, base, counter_of_print, 1);
	}
	else
	{
		print_nbr_in_base(nbr / b_size, base, counter_of_print, 0);
	}
	char_to_print = base[nbr % b_size];
	write(1, &char_to_print, 1);
	*counter_of_print = *counter_of_print + 1;
}

int	ft_putnbr_base_signed(int nbr, char *base)
{
	long	number;
	int		counter;

	counter = 0;
	number = nbr;
	if (nbr == -2147483648)
		return (write(1, "-2147483648", 11));
	if (nbr < 0)
	{
		counter += write(1, "-", 1);
		number = nbr * -1;
	}
	print_nbr_in_base(number, base, &counter, 0);
	return (counter);
}

int	ft_putnbr_base_unsigned(unsigned long int nbr, char *base)
{
	long	number;
	int		counter;

	counter = 0;
	number = nbr;
	print_nbr_in_base(number, base, &counter, 0);
	return (counter);
}
