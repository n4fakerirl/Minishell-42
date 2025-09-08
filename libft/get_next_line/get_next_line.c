/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 20:16:56 by ocviller          #+#    #+#             */
/*   Updated: 2025/07/08 21:38:03 by ocviller         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*fill_line_buffer(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(stash), NULL);
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(stash, buffer);
		if (!temp)
			return (NULL);
		free(stash);
		stash = temp;
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*set_line(char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!line)
		return (NULL);
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	tmp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!tmp || tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*stash;
	char		*line;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = fill_line_buffer(fd, stash, buffer);
	free(buffer);
	if (!line || line[0] == '\0')
	{
		free(line);
		stash = NULL;
		return (NULL);
	}
	stash = set_line(line);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int i = 0;

// 	fd = open("test.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
