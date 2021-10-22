/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycornamu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 16:09:27 by ycornamu          #+#    #+#             */
/*   Updated: 2021/10/22 14:17:02 by ycornamu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stddef.h>

typedef struct s_fd_list
{
	int					fd;
	int					nb_readed;
	char				*readed;
	struct s_fd_list	*next;
}			t_fd_list;

size_t	ft_strlen(const char *s);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strjoinbuf(char *s1, char s2[BUFFER_SIZE], const size_t s2_size);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

int		read_line(int fd, char **readed);
char	*return_line(char **readed);
char	*clean(t_fd_list **s, char full);
char	*get_next_line(int fd);

#endif
