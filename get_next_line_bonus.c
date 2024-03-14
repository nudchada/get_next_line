/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nusamank <nusamank@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:38:08 by nusamank          #+#    #+#             */
/*   Updated: 2024/03/08 15:26:19 by nusamank         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_to_str(int fd, char *str)
{
	char	*buffer;
	int		bytes;

	if (find_newline(str) >= 0)
		return (str);
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(str), NULL);
	bytes = 1;
	while (bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free(buffer), free(str), NULL);
		buffer[bytes] = '\0';
		str = concat_str(str, buffer);
		if (!str || find_newline(buffer) >= 0)
			break ;
	}
	free(buffer);
	return (str);
}

static char	*get_line(char *str, int n)
{
	char	*line;

	if (!str || !*str)
		return (NULL);
	if (n == -1)
		n = ft_strlen(str) - 1;
	line = ft_substr(str, 0, n + 1);
	return (line);
}

static char	*get_remainder(char	*str, int n)
{
	char	*remainder;
	int		len;

	if (n < 0)
		return (free(str), NULL);
	len = ft_strlen(str) - n - 1;
	if (len == 0)
		return (free(str), NULL);
	remainder = ft_substr(str, n + 1, len);
	free(str);
	return (remainder);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str[MAX_FD];
	int			newline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_to_str(fd, str[fd]);
	newline = find_newline(str[fd]);
	line = get_line(str[fd], newline);
	if (!line)
	{
		free(str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	str[fd] = get_remainder(str[fd], newline);
	return (line);
}

/*#include<fcntl.h>
#include<stdio.h>

int	main(void)
{
	int		fd[3];
	char	*lines[3];
	int		i;
	int		linesPrinted;

	fd[0] = open("t0.txt", O_RDONLY);
	fd[1] = open("t1.txt", O_RDONLY);
	fd[2] = open("t2.txt", O_RDONLY);

	while (1)
	{
		linesPrinted = 0;
		i = 0;
		while (i < 3)
		{
			lines[i] = get_next_line(fd[i]);
			if (lines[i])
			{
				printf("fd%i: %s\n", i, lines[i]);
				free(lines[i]);
				linesPrinted = 1;
			}
			i++;
		}
		if (!linesPrinted)
			break ;
	}
	i = 0;
	while (i < 3)
	{
		close(fd[i]);
		i++;
	}
	return (0);
}*/
