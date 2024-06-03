/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:30:43 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/11/03 15:30:47 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen_gnl(char *s, char c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

char	*ft_str_copy_until_n(char *s1, char *s2, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1 && s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] && (s2[j] != '\n'))
		str[i++] = s2[j++];
	if (s2[j] == '\n')
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	int		size_1;
	int		size_2;
	char	*str;

	size_1 = ft_strlen_gnl(s1, 0);
	size_2 = ft_strlen_gnl(s2, '\n');
	str = malloc (sizeof(char) * (size_1 + size_2 + 2));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	str = ft_str_copy_until_n(s1, s2, str);
	if (s1)
		free(s1);
	return (str);
}

void	update_array(char *buffer)
{
	int	size;
	int	offset;
	int	i;

	offset = 0;
	while (buffer[offset] != '\n' && buffer[offset])
		offset ++;
	offset ++;
	size = ft_strlen_gnl(buffer, 0);
	i = 0;
	while (offset < size)
		buffer[i++] = buffer[offset++];
	while (i <= BUFFER_SIZE)
		buffer[i++] = '\0';
}

char	*clean_buffer_bonus(char buffer[FOPEN_MAX][BUFFER_SIZE + 1], int fd)
{
	int	i;

	i = 0;
	if (fd >= 0 && fd < FOPEN_MAX)
	{
		while (buffer && buffer[fd][i] && i < BUFFER_SIZE)
		{
			buffer[fd][i] = '\0';
			i++;
		}
	}
	return (NULL);
}
