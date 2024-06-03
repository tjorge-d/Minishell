/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 14:27:52 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/10/17 14:27:54 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>

int		ft_printf(const char *s, ...);
int		ft_putnbr_base_signed(int nbr, char *base);
int		ft_putnbr_base_unsigned(unsigned long int nbr, char *base);
int		ft_print_char(char c);
int		ft_print_string(char *s);
int		ft_printf_d(int n);
int		ft_printf_u(unsigned int n);
int		ft_printf_hex_x(unsigned int n);
int		ft_printf_hex_maj(unsigned int n);
#endif
