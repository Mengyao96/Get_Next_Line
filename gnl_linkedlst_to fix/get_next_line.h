/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mezhang <mezhang@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 19:22:21 by mezhang           #+#    #+#             */
/*   Updated: 2025/07/24 18:55:42 by mezhang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# include <fcntl.h>

# include <stdlib.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

//GNL
char		*get_next_line(int fd);

//GNL_utils
void		*ft_calloc(size_t count, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin_gnl(char const *s1, char const *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);

void		*ft_memmove(void *des, const void *src, size_t len);
int  found_newline(t_list *stash);
char	*ft_strdup(const char *s);
void    lst_add_back(t_list **list, t_list *new_node);
t_list	*lst_new(char *content);




#endif
