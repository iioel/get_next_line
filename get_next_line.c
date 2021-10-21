/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/21 22:05:40 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*get_next_line(int fd)
{
	static char	*readed;
	static int	eof;
	size_t		nb_readed;

	if (read(fd, 0, 0))
		return (clean(&readed));
	if (readed == NULL)
	{
		readed = ft_calloc(1, sizeof(char));
		eof = 0;
	}
	if (ft_strchr(readed, '\n'))
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
	int		total_chars;
	int		total_buf;
	int		eof;

	total_chars = 0;
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
			total_chars += total_buf;
		}
	}
	return (total_chars);
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
