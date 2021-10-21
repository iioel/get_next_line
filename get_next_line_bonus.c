/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/22 01:01:22 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static t_fd_list	(*list)[2];

	if (read(fd, 0, 0))
		return (clean(&readed));
	list[1] = find_fd(list[1], fd);
	if (list[1] == NULL)
	{
		list[1] = ft_calloc(1, sizeof(t_fd_list));
		list[1]->readed = ft_calloc(1, sizeof(char));
		list[1]->eof = 0;
	}
	if (ft_strchr(list[1]->readed, '\n'))
		return (return_line(&readed));
	else if (! eof)
	{
		nb_readed = read_line(fd, &readed);
		if (nb_readed > 0 && *readed)
			return (return_line(&readed));
		else if (! nb_readed)
			eof = 1;
	}
	if (eof && *readed)
		return (return_line(&readed));
	return (clean(&readed));
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
		return (clean(readed));
	tmp = ft_substr(*readed, line_size, ft_strlen(*readed) - line_size);
	free(*readed);
	if (! tmp)
		return (clean(&out));
	*readed = tmp;
	return (out);
}

char	*clean(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
	return (NULL);
}

t_fd_list	*find_fd(t_fd_list *list, int fd)
{
	while (list)
	{
		if (list->fd == fd)
			return (list);
		list = list->next;
	}
	return (NULL)
}
