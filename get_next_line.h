/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpiriou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:23:00 by gpiriou           #+#    #+#             */
/*   Updated: 2021/02/04 13:51:48 by gpiriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct	s_list {
	int		fd;
	char	*temp;
}				t_list;

int				get_next_line(int fd, char **line);
int				ft_strlen(char *str);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(char *s1);
char			*ft_strndup(char *s1, int n);
char			*ft_strchr(char *s, int c);
char			*ft_substr(char *s, unsigned int start, size_t len);

#endif
