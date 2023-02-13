/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glpiriou <glpiriou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 20:33:03 by glpiriou          #+#    #+#             */
/*   Updated: 2023/02/13 15:32:41 by glpiriou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strcat(char *s1, char *s2)
{
	int	i;
	int	s1_len;

	i = 0;
	s1_len = ft_strlen(s1);
	while (s2[i])
	{
		s1[s1_len + i] = s2[i];
		i++;
	}
	s1[s1_len + i] = 0;
	return (s1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
		return (NULL);
	*s3 = '\0';
	ft_strcat(ft_strcat(s3, s1), s2);
	return (s3);
}

unsigned int	ft_strlen(char *str)
{
	unsigned int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strndup(char *s1, unsigned int n)
{
	unsigned int	i;
	char			*s1_dup;

	if (!s1)
		return (NULL);
	s1_dup = malloc((n + 1) * sizeof(char));
	i = 0;
	while (s1[i] && i < n)
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = 0;
	return (s1_dup);
}

int	ft_strchr(char *s, int c)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (i);
		i++;
	}
	return (0);
}
