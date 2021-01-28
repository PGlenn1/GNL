#include "get_next_line.h"

char *find_newline(char *str)
{
	char *str2;
	char *newline;
	static char *temp;

	if ((newline = ft_strchr(temp, '\n')))
	{
		str2 = ft_substr(temp, 0, newline - temp);
		temp = ft_strjoin(newline + 1, str);
	}
	else if ((newline = ft_strchr(str, '\n')))
	{
		if (!temp)
			str2 = ft_substr(str, 0, newline - str);
		else
			str2 = ft_strjoin(temp, ft_substr(str, 0, newline - str));
		temp = newline + 1;
	}
	else
	{
		if (!temp)
			str2 = str;
		else
			str2 = ft_strjoin(temp, str);
		newline = NULL;
	}
	return (str2);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	int ret;

	ret = read(fd, buff, BUFFER_SIZE);
	buff[ret] = '\0';
	*line = find_newline(ft_strndup(buff, BUFFER_SIZE));
	if (ret > 0 || **line)
	{
		return (1);
	}
	else if (ret == 0)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}

int main()
{
	char *str;
	int fd;
	int ret;

	str = NULL;
	fd = open("prout", O_RDONLY);
	ret = get_next_line(fd, &str);
	while (ret > 0)
		ret = get_next_line(fd, &str);
	return (0);
}
