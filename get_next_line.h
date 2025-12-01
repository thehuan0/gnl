/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jperez-s <jperez-s@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:35:54 by jperez-s          #+#    #+#             */
/*   Updated: 2025/11/18 10:44:50 by jperez-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlen(const char *s);

#endif