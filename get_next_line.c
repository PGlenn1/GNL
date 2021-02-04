/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpiriou <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 11:22:46 by gpiriou           #+#    #+#             */
/*   Updated: 2021/02/04 16:52:29 by gpiriou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*find_newline(char *str, char **temp)
{
	char *nl_str; /// NE PAS FREE STR
	char *index;

	nl_str = NULL;
	if ((index = ft_strchr(*temp, '\n')))
		nl_str = ft_substr(*temp, 0, index - *temp);
	else if ((index = ft_strchr(str, '\n')))
		nl_str = ft_substr(str, 0, index - str);
	if (index)
		*temp = ft_strndup(index + 1, ft_strlen(index + 1));
	else
	{
		if (str)
		{
			*temp = str;
		}
	}
	return (nl_str);
}

void	check_temp(char **temp, char **line, char **str, int ret)
{
	char *str2;

	str2 = NULL;
	if (ret == 0)
		*line = *temp;
	else
	{
		str2 = *str;
		*str = ft_strjoin(*temp, str2);
		free(str2);
	}
	*temp = NULL;
}

char	*ft_strjoin(char *s1, char *s2)
{
	char *s3;

	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	*s3 = '\0';
	ft_strcat(ft_strcat(s3, s1), s2);
	return (s3);
}

int		get_line(int fd, char **temp, char **line, int ret)
{
	char	buff[BUFFER_SIZE + 1];
	char	*str;

	str = NULL;
	while (!(*line = find_newline(str, temp)))
	{
		if (ret == 0)
		{
			if (*temp)
				check_temp(temp, line, &str, ret);
			else
			{
				*line = str;
				if (str) /// CA CHANGE RIEN, BIZARRE
					free(str);
			}
			break ;
		}
		if ((ret = read(fd, buff, BUFFER_SIZE)))
		{
			str = ft_strndup(buff, ret);
			if (*temp)
				check_temp(temp, line, &str, ret);
		}
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*temp;
	char		buff[1];
	int			ret;

	if (fd < 0 || !line || read(fd, buff, 0) < 0 || BUFFER_SIZE == 0)
		return (-1);
	ret = 1;
	ret = get_line(fd, &temp, line, ret);
	if (*line == NULL)
	{
		*line = ft_strndup("", 0);
	}
	if (ret > 0)
	{
		return (1);
	}
	else if (ret == 0)
	{
		free(temp);
		return (0);
	}
	else
		return (-1);
}

int main()
{
	char *str;
	int fd;
	int ret;

	str = NULL;
	fd = open("bigline.txt", O_RDONLY);
	while ((ret = get_next_line(fd, &str)));
		printf("*line: |%s\n", str);
	printf("*Line: |%s\n", str);
	return (0);
}
