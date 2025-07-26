/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:02:40 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/26 19:31:44 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	*ft_memmove(void *des, const void *src, size_t len)
{
	unsigned char		*m_des;
	const unsigned char	*m_src;

	if (des == NULL && src == NULL && len > 0)
		return (NULL);
	m_des = (unsigned char *)des;
	m_src = (const unsigned char *)src;
	if ((uintptr_t)m_des > (uintptr_t)m_src && (uintptr_t)m_des
		< (uintptr_t)m_src + len)
	{
		m_des = m_des + len - 1;
		m_src = m_src + len - 1;
		while (len--)
			*m_des-- = *m_src--;
	}
	else
	{
		while (len--)
			*m_des++ = *m_src++;
	}
	return (des);
}

static char	*read_a_line(int fd, char *chunk)
{
	char	*vault;
	int		bytes_read;
	char	*temp;

	vault = ft_strjoin(chunk, "");
	if (!vault)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(vault, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(vault), NULL);
		if (bytes_read == 0)
			break ;
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(vault, chunk);
		if (!temp)
			return (free(vault), NULL);
		free(vault);
		vault = temp;
	}
	return (vault);
}

static char	*to_line(char *vault)
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

static void	update(char *chunk)
{
	char	*chars_read;

	chars_read = ft_strchr(chunk, '\n');
	if (!chars_read)
	{
		chunk[0] = '\0';
		return ;
	}
	chars_read++;
	if (*chars_read == '\0')
	{
		chunk[0] = '\0';
		return ;
	}
	ft_memmove(chunk, chars_read, ft_strlen(chars_read) + 1);
}

char	*get_next_line(int fd)
{
	static char	chunk[BUFFER_SIZE + 1];
	char		*vault;
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vault = read_a_line(fd, chunk);
	if (!vault)
		return (chunk[0] = '\0', NULL);
	the_line = to_line(vault);
	free(vault);
	if (!the_line)
		return (chunk[0] = '\0', NULL);
	if (the_line[0] == '\0')
		return (free(the_line), chunk[0] = '\0', NULL);
	update(chunk);
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
} */
