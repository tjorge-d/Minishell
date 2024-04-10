/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjorge-d <tiagoscp2020@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:58:29 by tjorge-d          #+#    #+#             */
/*   Updated: 2024/04/10 16:40:21 by tjorge-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_space(char c)
{
	if (c == '\a' || c == '\b' || c == '\t' || c == '\n' \
		|| c == '\v' || c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == GREATER || c == LESS || c == V_BAR)
		return (1);
	return (0);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	fail_msg(char mode)
{
	if (mode == 'P')
		write(2, "Error: Failed to create a pipe\n", 32);
	else if (mode == 'M')
		write(2, "Error: Failed to allocate memory\n", 34);
	else if (mode == 'S')
		write(2, "Error: Invalid syntax\n", 23);
	else if (mode == 'F')
		write(2, "Error: Failed to fork the program\n", 35);
}
