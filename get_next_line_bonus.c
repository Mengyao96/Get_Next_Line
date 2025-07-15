/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:08:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/14 14:28:00 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_a_line(int fd, char *sub_vault)
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
		bytes_read = read(fd, chunk, BUFFER_SIZE); // supposed to be the buffersize
		if (bytes_read < 0)
			return (free(chunk), NULL);
		chunk[bytes_read] = '\0';  // converted to a string
		temp = ft_strjoin(sub_vault, chunk); //combine into a new string
		if (!temp)
			return (free(sub_vault), free(chunk), NULL);
		free(sub_vault);
		sub_vault = temp;
	}
	if (chunk)
		free(chunk);
	// printf("sub_vault is:\n%s", sub_vault);
	return (sub_vault);
}

//check new line in the collected buffers
char	*to_line(char *sub_vault)
{
	char	*line;
	size_t	i;

	if(!sub_vault || !*sub_vault)
		return (NULL);
	i = 0;
	while (sub_vault[i] && sub_vault[i] != '\n')
		i++;
	line = ft_substr(sub_vault, 0, i);
	return (line);
}

//update static vault
static char	*update(char *sub_vault)
{
	size_t	i;

	if(!sub_vault || !*sub_vault)
		return (NULL);
	i = 0;
	while (sub_vault[i] && sub_vault[i] != '\n')
		i++;
	if (sub_vault[i] == '\n')
		i++;
	if (i > ft_strlen(sub_vault))
		return (free(sub_vault), NULL);
	sub_vault = ft_substr(sub_vault, i, ft_strlen(sub_vault) - i);
	return (sub_vault);
}

char	*get_next_line(int fd)
{
	static char	*vault[OPEN_MAX]; //max 1024
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0 )//|| read(fd, 0, 0) < 0
		return (NULL);
	if (!vault[fd])
		vault[fd] = ft_calloc(1, sizeof(char));
	vault[fd] = read_a_line(fd, vault[fd]);
	if(vault[fd] == NULL)
		return (NULL);
	the_line = to_line(vault[fd]);
	vault[fd] = update(vault[fd]);
	return	(the_line);
}

/* int	main()
{
	int		a = open("./test.txt", O_RDONLY);//只读模式打开文件
	int		b = open("./test2.txt", O_RDONLY);//只读模式打开文件
	char	*new_line;
	int		count = 0;


	new_line = get_next_line(b);

	while (1)
	{
		if (new_line == NULL)  // every new line is a string
		{
			break;
		}
		count++;
		printf ("%dth line: \n%s\n", count, new_line);
		free(new_line);
		new_line = get_next_line(b);
	}
	close(b);
	return (0);
} */
