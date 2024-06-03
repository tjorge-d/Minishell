/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcota-pa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 15:30:29 by dcota-pa          #+#    #+#             */
/*   Updated: 2023/11/03 15:30:35 by dcota-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*next_line;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= FOPEN_MAX
		|| read(fd, buffer[fd], 0) < 0)
		return (clean_buffer_bonus(buffer, fd));
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE) > 0)
	{
		if (ft_strlen_gnl(buffer[fd], '\n') < ft_strlen_gnl(buffer[fd], 0) 
			|| buffer[fd][0] == '\n' || buffer[fd][BUFFER_SIZE - 1] == '\n')
		{
			next_line = ft_strjoin_gnl(next_line, buffer[fd]);
			update_array(buffer[fd]);
			return (next_line);
		}
		next_line = ft_strjoin_gnl(next_line, buffer[fd]);
		update_array(buffer[fd]);
		if (next_line == NULL)
			return (NULL);
	}
	return (next_line);
}
