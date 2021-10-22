/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/22 14:58:10 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>

t_fd_list	*find_fd(t_fd_list **list, int fd);

char	*get_next_line(int fd)
{
	static t_fd_list	*list[2];

	if (! list[0])
		list[0] = NULL;
	if (! list[1])
		list[1] = NULL;
	if (read(fd, 0, 0))
		return (clean(list, 1));
	list[1] = find_fd(&(list[0]), fd);
	if (ft_strchr(list[1]->readed, '\n'))
		return (return_line(&(list[1]->readed)));
	list[1]->nb_readed = read_line(fd, &(list[1]->readed));
	if (list[1]->nb_readed > 0 && *(list[1]->readed))
		return (return_line(&(list[1]->readed)));
	if (*(list[1]->readed))
		return (return_line(&(list[1]->readed)));
	return (clean(list, 0));
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
			*readed = ft_strjoinbuf(*readed, buf, total_buf);
	}
	return (1);
}

char	*return_line(char **readed)
{
	char	*out;
	char	*tmp;
	size_t	line_size;

	if (ft_strchr(*readed, '\n'))
		line_size = ft_strchr(*readed, '\n') - *readed + 1;
	else
		line_size = ft_strlen(*readed);
	out = ft_substr(*readed, 0, line_size);
	if (! out)
		free(*readed);
	if (! out)
		return (NULL);
	tmp = ft_substr(*readed, line_size, ft_strlen(*readed) - line_size);
	free(*readed);
	if (! tmp)
	{
		free(out);
		return (NULL);
	}
	*readed = tmp;
	return (out);
}

char	*clean(t_fd_list **s, char full)
{
	t_fd_list	**actual;
	t_fd_list	*next;
	t_fd_list	*prev;

	actual = &s[0];
	if (actual && *actual)
	{
		while (! full && *actual)
		{
			prev = *actual;
			if (*actual == s[1])
				break ;
			*actual = (*actual)->next;
		}
		while (*actual)
		{
			free((*actual)->readed);
			if (!full)
				prev->next = (*actual)->next;
			if (!full)
				(*actual)->next = NULL;
			next = (*actual)->next;
			free(*actual);
			actual = (t_fd_list **)next;
		}
	}	
	return (NULL);
}

t_fd_list	*find_fd(t_fd_list **list, int fd)
{
	t_fd_list	*out;
	t_fd_list	*prev;

	if (*list)
		while (*list)
		{
			prev = *list;
			if ((*list)->fd == fd)
				return (*list);
			*list = (*list)->next;
		}
	out = ft_calloc(1, sizeof(t_fd_list));
	if (! out)
		return (NULL);
	out->readed = ft_calloc(1, sizeof(char));
	out->fd = fd;
	out->next = NULL;
	if (! out)
		free(out);
	if (! out)
		return (NULL);
	if (! *list)
		*list = out;
	else
		prev->next = out;
	return (out);
}
