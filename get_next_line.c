/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:02:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 14:30:35 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_a_line(int fd, char *vault)
{
	char	*chunk;
	size_t	bytes_read;
	char	*temp;

	chunk = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!chunk)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(chunk, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(chunk), NULL);
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(vault, chunk);
		if (!temp)
			return (free(vault), free(chunk), NULL);
		free(vault);
		vault = temp;
	}
	if (chunk)
		free(chunk);
	return (vault);
}

//check new line in the collected buffers
char	*to_line(char *vault)
{
	char	*line;
	size_t	i;

	if(!vault || !*vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	line = ft_substr(vault, 0, i);
	return (line);
}

//update static vault
static char	*update(char *vault)
{
	size_t	i;

	if(!vault || !*vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	if (vault[i] == '\n')
		i++;
	if (i > ft_strlen(vault))
		return (free(vault), NULL);
	vault = ft_substr(vault, i, ft_strlen(vault) - i);
	return (vault);
}

char	*get_next_line(int fd)
{
	static char	*vault;
	char		*the_line;


	if (fd < 0 || BUFFER_SIZE <= 0 )//|| read(fd, 0, 0) < 0
		return (NULL);
	if (!vault)
		vault = ft_calloc(1, sizeof(char));
	vault = read_a_line(fd, vault);
	if(vault == NULL)
		return (NULL);
	the_line = to_line(vault);
	vault = update(vault);
	return	(the_line);
}

/* int	main()
{
	int		fd = open("./test.txt", O_RDONLY);//只读模式打开文件
	char	*new_line;
	int		count = 0;

	new_line = get_next_line(fd);

	while (1)
	{
		if (new_line == NULL)  // every new line is a string
		{
			break;
		}
		count++;
		printf ("%dth line: \n%s\n", count, new_line);
		free(new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (0);
} */
