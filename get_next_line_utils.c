/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpiriou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:23:07 by gpiriou           #+#    #+#             */
/*   Updated: 2021/02/04 13:58:18 by gpiriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

static char	*ft_strcat(char *s1, char *s2)
{
	int i;
	int s1_len;

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

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	s_unsigned;
	char			*str;

	if (!s)
		return (NULL);
	s_unsigned = (unsigned int)ft_strlen(s);
	if (!(str = malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < len && start < s_unsigned)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strchr(char *s, int c)
{
	unsigned char	char_c;
	unsigned int	i;

	char_c = (unsigned char)c;
	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == char_c)
			return (&s[i]);
		i++;
	}
	if (s[i] == char_c)
		return (&s[i]);
	else
		return (NULL);
}

char		*ft_strndup(char *s1, int n)
{
	int		i;
	char	*s1_dup;

	i = 0;
	if (!(s1_dup = malloc((n + 1) * sizeof(char))))
		return (NULL);
	while (s1[i] && i < n)
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	return (s1_dup);
}
