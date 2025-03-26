/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: makboga <makboga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:12:03 by makboga           #+#    #+#             */
/*   Updated: 2025/03/20 13:16:34 by makboga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*move_str(char **str, size_t n)
{
	char	*old;
	size_t	len;

	old = *str;
	len = f_strlen(*str) - n;
	if (len == 0)
		*str = NULL;
	else
		*str = f_substr(old, n, len);
	free(old);
	return (*str);
}

char	*strappend(char **str, char *str2)
{
	char	*old;

	old = *str;
	*str = f_strjoin(old, str2);
	if (old)
		free(old);
	return (0);
}

char	*get_data(char **backup, int fd)
{
	char	buffer[BUFFER_SIZE + 1];
	int		readed_byte;

	readed_byte = 1;
	while (!(f_strchr(*backup, '\n')) && readed_byte > 0)
	{
		readed_byte = read(fd, buffer, BUFFER_SIZE);
		buffer[readed_byte] = 0;
		if (readed_byte <= 0)
			break ;
		strappend(backup, buffer);
	}
	return (*backup);
}

char	*get_line(char **str)
{
	char	*line;
	size_t	new_len;

	if (f_strchr(*str, '\n'))
	{
		new_len = f_strchr(*str, '\n') - (*str);
		line = f_substr(*str, 0, new_len);
		move_str(str, new_len);
		return (line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*line;

	get_data(&buffer, fd);
	line = get_line(&buffer);
	if (line == NULL)
	{
		line = f_strdup(buffer);
		free(buffer);
		buffer = NULL;
	}
	return (line);
}
