/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: azerfaou <azerfaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:28:32 by azerfaou          #+#    #+#             */
/*   Updated: 2024/12/31 22:34:44 by azerfaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str_result;

	if (!s1 && !s2)
		return (NULL);
	str_result = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1,
			sizeof(char));
	if (!str_result)
		return (NULL);
	ft_strncpy(str_result, s1, ft_strlen(s1));
	ft_strncpy(str_result + ft_strlen(s1), s2, ft_strlen(s2));
	return (str_result);
}

static char	*extract_and_update(char *new_line_ptr, char **remainder)
{
	size_t	line_len;
	char	*new_remainder;
	char	*line;

	new_remainder = NULL;
	line = NULL;
	line_len = new_line_ptr - *remainder + 1;
	line = (char *)ft_calloc(line_len + 1, sizeof(char));
	if (!line)
		return (NULL);
	ft_strncpy(line, *remainder, line_len);
	if (*(new_line_ptr + 1) != '\0')
	{
		new_remainder = ft_strdup(new_line_ptr + 1);
		if (!new_remainder)
			return (NULL);
	}
	// free(*remainder);
	*remainder = new_remainder;
	return (line);
}

static ssize_t	read_and_append(int fd, char **remainder)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*new_remainder;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
		buffer[bytes_read] = '\0';
	else
		return (bytes_read);
	if (!(*remainder))
	{
		*remainder = ft_strdup(buffer);
		if (!*remainder)
			return (-1);
	}
	else
	{
		new_remainder = ft_strjoin_gnl(*remainder, buffer);
		if (!new_remainder)
			return (*remainder = NULL, -1);
		// free(*remainder);
		*remainder = new_remainder;
	}
	return (bytes_read);
}

/***
 * @brief this function handles the end of file
 * @param line the line to be returned
 * @param remainder the remainder of the file reading
 * @return void
 *
 * @note you must free the reminder before checking line
 */
static void	handle_eof(char **line, char **remainder)
{
	if (*remainder && **remainder)
	{
		*line = ft_strdup(*remainder);
		// free(*remainder);
		*remainder = NULL;
		if (!*line)
			return ;
	}
	else
		*line = NULL;
}

/**
 * @brief this function reads a file line by line
 * @param fd the file descriptor
 * @return char* the line read
 *
 * @note
 */
char	*get_next_line(int fd)
{
	ssize_t		bytes_read;
	char		*new_line_ptr;
	char		*line;
	static char	*remainder = NULL;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (remainder = NULL, NULL);
	while (1)
	{
		bytes_read = read_and_append(fd, &remainder);
		if (bytes_read < 0)
			return (remainder = NULL, NULL);
		new_line_ptr = ft_strchr(remainder, '\n');
		if (new_line_ptr)
			return (line = extract_and_update(new_line_ptr, &remainder), line);
		if (bytes_read == 0)
		{
			if (remainder && *remainder)
				return (handle_eof(&line, &remainder), remainder = NULL, line);
			else if (bytes_read == 0)
				return (remainder = NULL, NULL);
		}
	}
}
