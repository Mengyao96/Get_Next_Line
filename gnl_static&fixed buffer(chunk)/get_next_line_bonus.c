/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:08:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/26 19:30:14 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static char	*to_line(char *sub_vault)
{
	size_t	i;

	if (!sub_vault || !*sub_vault)
		return (NULL);
	i = 0;
	while (sub_vault[i] && sub_vault[i] != '\n')
		i++;
	if (sub_vault[i] == '\n')
		i++;
	return (ft_substr(sub_vault, 0, i));
}

static void	update(char *last_chunk)
{
	char	*read_part;

	read_part = ft_strchr(last_chunk, '\n');
	if (!read_part)
	{
		last_chunk[0] = '\0';
		return ;
	}
	read_part++;
	if (*read_part == '\0')
	{
		last_chunk[0] = '\0';
		return ;
	}
	ft_memmove(last_chunk, read_part, ft_strlen(read_part) + 1);
}

char	*get_next_line(int fd)
{
	static char	chunk_unit[OPEN_MAX][BUFFER_SIZE + 1];
	char		*vault[OPEN_MAX];
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	vault[fd] = read_a_line(fd, chunk_unit[fd]);
	if (!vault[fd])
		return (chunk_unit[fd][0] = '\0', NULL);
	the_line = to_line(vault[fd]);
	free(vault[fd]);
	if (!the_line)
		return (chunk_unit[fd][0] = '\0', NULL);
	if (the_line[0] == '\0')
		return (free(the_line), chunk_unit[fd][0] = '\0', NULL);
	update(chunk_unit[fd]);
	return (the_line);
}

/* void	leak()
{
	system("leaks -q a.out");
}

int	main()
{

	atexit(leak);

	int		a = open("./test.txt", O_RDONLY);
	int		b = open("./test2.txt", O_RDONLY);
	char	*new_line;
	int		count = 0;


	new_line = get_next_line(b);

	while (1)
	{
		if (new_line == NULL)
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
