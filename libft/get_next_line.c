/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bryaloo <bryaloo@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 21:42:24 by bryaloo           #+#    #+#             */
/*   Updated: 2024/10/11 21:43:05 by bryaloo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define MAX_FD 512

static int	read_and_concat(int fd, char **remain, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (bytes_read);
	buffer[bytes_read] = '\0';
	if (*remain == NULL)
		*remain = ft_strdup("");
	temp = ft_strjoin(*remain, buffer);
	free(*remain);
	if (!temp)
		return (-1);
	*remain = temp;
	return (bytes_read);
}

static char	*extract_line(char **remain)
{
	char	*line;
	char	*newline_pos;
	char	*temp;

	if (*remain == NULL)
		return (NULL);
	newline_pos = ft_strchr(*remain, '\n');
	if (newline_pos)
	{
		line = ft_substr(*remain, 0, newline_pos - *remain + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*remain);
		*remain = temp;
		if (!(*remain))
		{
			free(line);
			return (NULL);
		}
		return (line);
	}
	else
		return (NULL);
}

static char	*handle_remain(char **remain, char *line)
{
	if (line)
		free(line);
	line = ft_strdup(*remain);
	free(*remain);
	*remain = NULL;
	return (line);
}

static char	*read_line(int fd, char **remain, char *buffer)
{
	char	*line;
	int		bytes_read;

	line = NULL;
	bytes_read = 1;
	if (!remain[fd] || !*remain[fd])
		bytes_read = read_and_concat(fd, &remain[fd], buffer);
	while (bytes_read > 0)
	{
		line = extract_line(&remain[fd]);
		if (line)
			break ;
		bytes_read = read_and_concat(fd, &remain[fd], buffer);
	}
	if (bytes_read == 0 && remain[fd] && *remain[fd])
		line = handle_remain(&remain[fd], line);
	else if (bytes_read == 0 && remain[fd] && !*remain[fd])
		free(remain[fd]);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*remain[MAX_FD];
	char		*buffer;
	char		*line;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_line(fd, remain, buffer);
	free(buffer);
	return (line);
}
