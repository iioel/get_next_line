/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:08:45 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/20 19:06:58 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

char	*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE], const size_t s2_size);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);

char	*get_next_line(int fd)
{
	static char	*readed;
	size_t		nb_readed;
	size_t		line_size;
	char		buf[BUFFER_SIZE];
	char		*tmp;

	if (readed == NULL)
		readed = ft_calloc(1, sizeof(char));
	while (read(fd, NULL, 0) >= 0)
	{
		nb_readed = read(fd, buf, BUFFER_SIZE);
		readed = ft_strjoinbuf(readed, buf, nb_readed);
		if (! readed)
			return (NULL);
		if (ft_strchr(readed, '\n') != NULL)
			break ;
	}
	line_size = ft_strchr(readed, '\n') - readed;
	tmp = ft_substr(readed, 0, line_size);
	readed = ft_substr(readed, line_size, ft_strlen(readed) - line_size);
	if (! tmp || ! readed)
		return (NULL);
	return (tmp);
}
