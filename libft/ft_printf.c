/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:27:45 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/17 14:27:47 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_pointer(void *pointer)
{
	if (!pointer)
		return (write(1, "(nil)", 5));
	write (1, "0x", 2);
	return (ft_putnbr_base_unsigned((unsigned long int) pointer, 
			("0123456789abcdef")) + 2);
}

static int	separate_print(const char c, va_list args)
{
	if (c == 0)
		return (0);
	if (c == 'd' || c == 'i')
		return (ft_printf_d(va_arg(args, int)));
	if (c == 'u')
		return (ft_printf_u(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_printf_hex_x(va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_printf_hex_maj(va_arg(args, unsigned int)));
	if (c == 'p')
		return (ft_print_pointer(va_arg(args, void *)));
	if (c == 's')
		return (ft_print_string(va_arg(args, char *)));
	if (c == 'c')
		return (ft_print_char(va_arg(args, unsigned int)));
	if (c == '%')
		return (ft_print_char('%'));
	else
	{
		ft_print_char('%');
		return (ft_print_char(c) + 1);
	}
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		printed_counter;
	int		i;

	i = 0;
	if (s == NULL)
		return (-1);
	va_start(args, s);
	printed_counter = 0; 
	while (s[i] != '\0')
	{
		if (s[i] == '%')
		{
			if (s[i + 1] != '\0')
				printed_counter += separate_print(s[++i], args);
			else
				printed_counter += write(1, "%", 1);
		}
		else 
			printed_counter += ft_print_char(s[i]);
		i++;
	}
	return (printed_counter);
}

/*int main(void)
{

	ft_printf(" %%%{\n");
	printf(" %%%{\n");

}*/