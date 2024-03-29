/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbueno-s <sbueno-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:08:08 by sbueno-s          #+#    #+#             */
/*   Updated: 2023/11/22 14:10:36 by sbueno-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_linetrim(char *warehouse)
{
	int		i;
	char	*line;

	i = 0;
	if (!warehouse[i])
		return (NULL);
	while (warehouse[i] && warehouse[i] != '\n')
		i++;
	if (warehouse[i] == '\0')
		line = (char *)malloc(sizeof(char) * (i + 1));
	else
		line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (warehouse[i] && warehouse[i] != '\n')
	{
		line[i] = warehouse[i];
		i++;
	}
	if (warehouse[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_sc_copy(char *warehouse, char *newhouse, size_t start, size_t end)
{
	size_t	i;

	i = start;
	while (i < end)
	{
		newhouse[i - start] = warehouse[i];
		i++;
	}
	newhouse[i - start] = '\0';
	return (newhouse);
}

char	*ft_static_clean(char *warehouse, char *linetoprint)
{
	size_t	len;
	size_t	i;
	char	*newhouse;

	len = ft_strlen(warehouse) - ft_strlen(linetoprint);
	if (len == 0)
	{
		free(warehouse);
		return (NULL);
	}
	newhouse = malloc(len + 1);
	if (!newhouse)
		return (NULL);
	i = 0;
	while (warehouse[i] != '\n' && warehouse[i] != '\0')
		i++;
	i++;
	newhouse = ft_sc_copy(warehouse, newhouse, i, ft_strlen(warehouse));
	free(warehouse);
	return (newhouse);
}

char	*read_cicle(char *warehouse, int fd, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(warehouse, '\n') == NULL)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			free(warehouse);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		warehouse = ft_strjoin(warehouse, buffer);
	}
	return (warehouse);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*line;
	static char	*warehouse;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	warehouse = read_cicle(warehouse, fd, buffer);
	if (!warehouse)
		return (NULL);
	line = ft_linetrim(warehouse);
	warehouse = ft_static_clean(warehouse, line);
	free(buffer);
	return (line);
}

/* int	main(void)
{
	char	*line;

	int	fd = open("text.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("the file is not opening :/");
		return (-1);
	}	
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return(0);
} */