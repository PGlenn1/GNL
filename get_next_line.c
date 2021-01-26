#include "get_next_line.h"

char *find_newline(char *str)
{
	static char *str2;
	char *newline;

	if ((newline = ft_strchr(str, '\n')))
	{
		str2 = ft_substr(str, 0, newline - str);
	}
	else
		str2 = str;
	return (str2);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	int ret;

	while ((ret = read(fd, buff, BUFFER_SIZE)))
	{
		buff[ret] = '\0';
		*line = find_newline(ft_strndup(buff, BUFFER_SIZE));
		printf("\nbuff:%s\n", buff);
	}
	return (0);
}

int main()
{
	char *str;
	int fd;
	int ret;

	str = NULL;
	fd = open("prout", O_RDONLY);
	ret = get_next_line(fd, &str)
	while (ret > 0);
	if (ret == 0)
		return (0);
	if (ret > -1)
		return (1);
	return (0);
}
