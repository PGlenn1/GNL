/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glpiriou <glpiriou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:36:20 by glpiriou          #+#    #+#             */
/*   Updated: 2023/02/13 16:54:39 by glpiriou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <strings.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef ARRAY_SIZE
#  define ARRAY_SIZE 1024
# endif

typedef struct s_fd_data
{
	int			fd;
	char		*save;
}				t_fd_data;

int				ft_strchr(char *s, int c);
char			*ft_strjoin(char *s1, char *s2);
unsigned int	ft_strlen(char *str);
char			*ft_strndup(char *s1, unsigned int n);
char			*get_next_line(int fd);

#endif
