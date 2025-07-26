/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 13:08:24 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/26 19:42:54 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clean_up(void **ptr)
{
	void	*temp;

	if (!ptr || !*ptr)
		return ;
	temp = *ptr;
	free(temp);
	*ptr = NULL;
}

static char	*read_a_line(int fd, char *sub_vault)
{
	char	chunk[BUFFER_SIZE + 1];
	size_t	bytes_read;
	char	*temp;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(sub_vault, '\n'))
	{
		bytes_read = read(fd, chunk, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean_up((void **)&sub_vault), NULL);
		if (bytes_read == 0)
			break ;
		chunk[bytes_read] = '\0';
		temp = ft_strjoin(sub_vault, chunk);
		if (!temp)
			return (clean_up((void **)&sub_vault), NULL);
		clean_up((void **)&sub_vault);
		sub_vault = temp;
	}
	return (sub_vault);
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

static char	*update(char *sub_vault, char *the_line)
{
	size_t	len_vault;
	size_t	len_line;
	char	*new_vault;

	if (!sub_vault)
		return (NULL);
	len_vault = ft_strlen(sub_vault);
	len_line = ft_strlen(the_line);
	if (len_line == len_vault)
		return (clean_up((void **)&sub_vault), NULL);
	new_vault = ft_substr(sub_vault, len_line, len_vault - len_line);
	if (!new_vault)
		return (clean_up((void **)&sub_vault), NULL);
	return (clean_up((void **)&sub_vault), new_vault);
}

char	*get_next_line(int fd)
{
	static char	*vault[OPEN_MAX];
	char		*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (clean_up((void **)&vault[fd]), NULL);
	if (!vault[fd])
	{
		vault[fd] = ft_calloc(1, sizeof(char));
		if (!vault[fd])
			return (NULL);
	}
	vault[fd] = read_a_line(fd, vault[fd]);
	if (vault[fd] == NULL)
		return (NULL);
	the_line = to_line(vault[fd]);
	if (!the_line)
		return (clean_up((void **)&vault[fd]), NULL);
	vault[fd] = update(vault[fd], the_line);
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
