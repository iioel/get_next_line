/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/22 17:48:38 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>

// In get_next_line_utils_bonus.c
char		*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE],
				const size_t s2_size);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strchr(const char *s, int c);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlen(const char *s);

// In this file
typedef struct s_fd_list
{
	int					fd;
	char				*readed;
	struct s_fd_list	*next;
}			t_fd_list;
int			read_line(int fd, char **readed);
char		*return_line(t_fd_list **list);
char		*clean(t_fd_list **s);
t_fd_list	*find_fd(t_fd_list **list, int fd);

char	*get_next_line(int fd)
{
	static t_fd_list	*list[2];

	if (read(fd, 0, 0))
		return (NULL);
	list[1] = find_fd(&(list[0]), fd);
	if (ft_strchr(list[1]->readed, '\n'))
		return (return_line(list));
	if (read_line(fd, &(list[1]->readed)) > 0 && *(list[1]->readed))
		return (return_line(list));
	return (clean(list));
}

int	read_line(int fd, char **readed)
{
	char	buf[BUFFER_SIZE];
	int		total_buf;
	int		eof;

	total_buf = 0;
	eof = 0;
	while (! eof && ! ft_strchr(*readed, '\n'))
	{
		total_buf = read(fd, buf, BUFFER_SIZE);
		if (total_buf < 0)
			return (-1);
		else if (total_buf == 0)
			eof = 1;
		else
		{
			*readed = ft_strjoinbuf(*readed, buf, total_buf);
			if (! *readed)
				return (-1);
		}
	}
	return (1);
}

char	*return_line(t_fd_list **list)
{
	char	*out;
	char	*tmp;
	size_t	line_size;

	if (ft_strchr(list[1]->readed, '\n'))
		line_size = ft_strchr(list[1]->readed, '\n') - list[1]->readed + 1;
	else
		line_size = ft_strlen(list[1]->readed);
	out = ft_substr(list[1]->readed, 0, line_size);
	if (! out)
		return (clean(list));
	if (! ft_strchr(list[1]->readed, '\n'))
	{
		clean(list);
		return (out);
	}
	tmp = ft_substr(list[1]->readed, line_size,
			ft_strlen(list[1]->readed) - line_size);
	free(list[1]->readed);
	if (! tmp)
		free(out);
	if (! tmp)
		return (NULL);
	list[1]->readed = tmp;
	return (out);
}

char	*clean(t_fd_list **s)
{
	t_fd_list	*actual;
	t_fd_list	*prev;

	actual = s[0];
	if (actual && actual == s[1])
	{
		s[0] = actual->next;
		free(actual->readed);
		free(actual);
		return (NULL);
	}
	while (actual && actual != s[1])
	{
		prev = actual;
		actual = actual->next;
	}
	while (actual != NULL)
	{
		prev->next = actual->next;
		free(actual->readed);
		free(actual);
	}
	return (NULL);
}

t_fd_list	*find_fd(t_fd_list **list, int fd)
{
	t_fd_list	*node[3];

	node[1] = *list;
	if (node[1])
	{
		while (node[1])
		{
			node[0] = node[1];
			if (node[1]->fd == fd)
				return (node[1]);
			node[1] = node[1]->next;
		}
	}
	node[2] = ft_calloc(1, sizeof(t_fd_list));
	if (! node[2])
		return (NULL);
	node[2]->readed = ft_calloc(1, sizeof(char));
	node[2]->fd = fd;
	node[2]->next = NULL;
	if (! *list)
		*list = node[2];
	else
		node[0]->next = node[2];
	return (node[2]);
}
