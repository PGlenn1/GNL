#include "get_next_line.h"

char *find_newline(char *str, char **temp)
{
	char *nl_str;
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
			*temp = str;
	}
	return (nl_str);
}

int	get_line(int fd, char **temp, char **line)
{
	int ret;
	char buff[BUFFER_SIZE + 1];
	char *str;

	str = NULL;
	ret = 1;
	while (!(*line = find_newline(str, temp)))
	{
		if (ret == 0)
		{
			if (*temp)
			{
				*line = *temp;
				*temp = NULL;
			}
			else
				*line = str;
			break;
		}
		if ((ret = read(fd, buff, BUFFER_SIZE)))
		{
			str = ft_strndup(buff, ret);
			if (*temp)
			{
				str = ft_strjoin(*temp, str);
				*temp = NULL;
			}
		}
	}
	return (ret);
}


int	get_next_line(int fd, char **line)
{
	static char *temp;
	char buff[1];
	int ret;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	ret = get_line(fd, &temp, line);
	if (*line == NULL)
		*line = ft_strndup("", 0);
	if (ret > 0)
		return (1);
	else if (ret == 0)
		return (0);
	else
		return (-1);
}

//int main()
//{
//	char *str;
//	int fd;
////	int fd2;
//	int ret;
//
//	str = NULL;
//	fd = open("alphabet", O_RDONLY);
////	fd2 = open("half_marge_bottom", O_RDONLY);
//	while ((ret = get_next_line(fd, &str)))
//		printf("*line: |%s\n", str);
////	printf("*Line: |%s\n", str);
////	while ((ret = get_next_line(fd2, &str)))
////		printf("*line: |%s\n", str);
////	printf("*Line: |%s\n", str);
//	return (0);
//}
