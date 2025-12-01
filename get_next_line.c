/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-s <jperez-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:50:20 by jperez-s          #+#    #+#             */
/*   Updated: 2025/10/14 08:28:25 by jperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*update_stash(char *stash)
{
	char	*new_stash;
	size_t	i;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	if (stash[i] == '\0')
		return (free(stash), NULL);
	new_stash = ft_substr(stash, i, ft_strlen(stash) - i);
	free(stash);
	return (new_stash);
}

static char	*get_line(char *stash)
{
	size_t	i;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static int	read_to_stash(int fd, char **stash, char *buffer)
{
	char	*temp;
	int		bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		temp = *stash;
		*stash = ft_strjoin(*stash, buffer);
		free(temp);
		if (!*stash)
			return (-1);
		if (ft_strchr(*stash, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	return (bytes);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = ft_strdup("");
		if (!stash)
			return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), stash = NULL, NULL);
	bytes = read_to_stash(fd, &stash, buffer);
	free(buffer);
	if (bytes < 0)
		return (free(stash), stash = NULL, NULL);
	line = get_line(stash);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	stash = update_stash(stash);
	return (line);
}
