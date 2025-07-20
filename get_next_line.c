/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:02:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/20 15:00:11 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void clean_up(void **vault)
{
	if (vault && *vault)
	{
		free(*vault);
		*vault = NULL;
	}
}

static char	*read_a_line(int fd, char *vault)
{
	char	*chunk;
	int		bytes_read;
	char	*temp;

	chunk = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!chunk)
		return (NULL);
	if (!vault)
	{
		vault = ft_calloc(1, sizeof(char));
		if (!vault)
			return (clean_up((void **)&chunk), NULL);
	}
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(vault, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_up((void **)&chunk), NULL);
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(vault, chunk);
		clean_up((void **)&vault);
		vault = temp;
	}
	return (clean_up((void **)&chunk), vault);
}

static char	*to_line(char *vault)
{
	char	*line;
	size_t	i;

	if(!vault || !*vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	if (vault[i] == '\n')
		i++;
	line = ft_substr(vault, 0, i);
	return (line);
	// return(ft_substr(vault, 0, i));
}

static char	*update(char *vault)
{
	size_t	i;
	char	*new_vault;
	size_t	len;

	if(!vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	if (vault[i] == '\n')
		i++;
	len = ft_strlen(vault);
	if (i >= len)
		return (clean_up((void **)&vault), NULL);
	new_vault = ft_substr(vault, i, len - i);
	if (!new_vault)
		return (clean_up((void **)&vault), NULL);
	return (clean_up((void **)&vault), new_vault);
}


char	*get_next_line(int fd)
{
	static char	*vault;
	char	*temp;
	char	*the_line;
	char	*new_vault;

	if (!vault)
	{
		vault = ft_calloc(1, sizeof(char));
		if (!vault)
			return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		clean_up((void **)&vault);
		vault = NULL;
		return (NULL);
	}
	temp = read_a_line(fd, vault);
	if(temp == NULL)
	{
		clean_up((void **)&vault);
		vault = NULL;
		return (NULL);
	}
	vault = temp;

	the_line = to_line(vault);
	if (!the_line)
	{
		clean_up((void **)&vault);
		vault = NULL;
		return (NULL);
	}
	new_vault = update(vault);
	if (!new_vault)
		vault = NULL;
	else
		vault = new_vault;
	return	(the_line);
}

/* int	main(void)
{
	int		fd = open("./test5.txt", O_RDONLY);
	char	*new_line;
	int		count = 0;

	new_line = get_next_line(fd);

	while (1)
	{
		if (new_line == NULL)
			break;
		count++;
		printf("%s", new_line);
		free(new_line);
		new_line = get_next_line(fd);
	}
	close(fd);
	return (0);
} */
