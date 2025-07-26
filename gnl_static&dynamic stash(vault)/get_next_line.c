/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:02:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/26 19:41:30 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	clean_up(void **vault)
{
	void	*temp;

	if (!vault || !*vault)
		return ;
	temp = *vault;
	free(temp);
	*vault = NULL;
}

char	*read_a_line(int fd, char *ptr)
{
	char	chunk[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(ptr, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_up((void **)&ptr), NULL);
		if (bytes_read == 0)
			break ;
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(ptr, chunk);
		if (!temp)
			return (clean_up((void **)&ptr), NULL);
		clean_up((void **)&ptr);
		ptr = temp;
	}
	return (ptr);
}

char	*to_line(char *vault)
{
	size_t	i;

	if (!vault || !*vault)
		return (NULL);
	i = 0;
	while (vault[i] && vault[i] != '\n')
		i++;
	if (vault[i] == '\n')
		i++;
	return (ft_substr(vault, 0, i));
}

char	*update(char *vault, char *the_line)
{
	size_t	len_vault;
	size_t	len_line;
	char	*new_vault;

	if (!vault)
		return (NULL);
	len_vault = ft_strlen(vault);
	len_line = ft_strlen(the_line);
	if (len_line == len_vault)
		return (clean_up((void **)&vault), NULL);
	new_vault = ft_substr(vault, len_line, len_vault - len_line);
	if (!new_vault)
		return (clean_up((void **)&vault), NULL);
	return (clean_up((void **)&vault), new_vault);
}

char	*get_next_line(int fd)
{
	static char	*vault;
	char		*the_line;
	char		*new_vault;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (clean_up((void **)&vault), NULL);
	if (!vault)
	{
		vault = ft_calloc(1, sizeof(char));
		if (!vault)
			return (NULL);
	}
	vault = read_a_line(fd, vault);
	if (!vault)
		return (NULL);
	the_line = to_line(vault);
	if (!the_line)
		return (clean_up((void **)&vault), NULL);
	new_vault = update(vault, the_line);
	vault = new_vault;
	return (the_line);
}

/* #include <string.h>

void	leak()
{
	system("leaks -q a.out");
}

void gnl(int fd, char *expected)
{
	char *line = get_next_line(fd);
	if (line == NULL && expected == NULL)
		return;
	if (line != NULL && expected != NULL && strcmp(line, expected) == 0)
	{
		printf("Test passed: %s\n", line);
		free(line);
		return;
	}
	printf("Test failed: expected '%s', got '%s'\n", expected, line ?
		line : "NULL");
}

*/
