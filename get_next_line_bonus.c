/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-s <jperez-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:32:14 by jperez-s          #+#    #+#             */
/*   Updated: 2025/10/13 17:32:14 by jperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;
	char		*buffer;
	int			bytes;

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash[fd])
	{
		stash[fd] = ft_strdup("");
		if (!stash[fd])
			return (NULL);
	}
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	bytes = read_to_stash(fd, &stash[fd], buffer);
	free(buffer);
	if (bytes < 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	line = get_line(stash[fd]);
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = update_stash(stash[fd]);
	return (line);
}
