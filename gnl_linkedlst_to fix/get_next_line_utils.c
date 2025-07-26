/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:37:43 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/24 19:00:50 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_list	*lst_new(char *content)
{
    t_list  *new_node;

    if (!content)
		return (NULL);
	new_node = (t_list *)malloc(sizeof(t_list));
    if (!new_node)
        return (NULL);
    new_node->content = content;
    new_node->next = NULL;
    return (new_node);
}

void    lst_add_back(t_list **list, t_list *new_node)
{
    t_list  *current;

    if (!list || !new_node)
        return;
    if (*list == NULL)
    {
        *list = new_node;
        return;
    }
    current = *list;
    while (current->next)
        current = current->next;
    current->next = new_node;
}

int  found_newline(t_list *stash)
{
	t_list  *current;

	if (!stash)
		return (0);
	current = stash;
	while (current)
	{
		if (ft_strchr(current->content, '\n'))
			return (1);
		current = current->next;
	}
		return (0);
}
char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	i;
	size_t	len;

	len = ft_strlen(s);
	i = 0;
	ptr = (char *)malloc(sizeof(char) * len + 1);
	if (ptr == NULL)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if (s == NULL)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (len == 0 || start >= s_len)
	{
		substring = ft_calloc(1, 1);
		if (!substring)
			return (NULL);
		return (substring);
	}
	if (s_len - start < len)
		len = s_len - start;
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < len/*  && s[start + i] != '\0' */)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	size_t				i;
	unsigned char		*ptr1;
	unsigned char	*ptr2;

	i = 0;
	if (!dst && !src)
		return (NULL);
	ptr1 = (unsigned char *)dst;
	ptr2 = (unsigned char *)src;
	while (i < n)
	{
		ptr1[i] = ptr2[i];
		i++;
	}
	return (dst);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;
	size_t	i;

	total = count * size;
	ptr = (char *)malloc(total);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}


char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	total_len;
	size_t	s1_len;
	size_t	count;

	s1_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	total_len = s1_len + ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (total_len + 1));
	if (ptr == NULL)
		return (NULL);
	count = 0;
	while (*s1)
		ptr[count++] = *s1++;
	while (*s2)
		ptr[count++] = *s2++;
	ptr[count] = '\0';
	free((char *)s1);
	return (ptr);
}


void	*ft_memmove(void *des, const void *src, size_t len)
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
