#include "get_next_line.h"

char *find_newline(char *str, char **temp)
{
	char *nl_str;
	char *index;

	if (!str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index)
	{
		nl_str = ft_substr(str, 0, index - str);
		if (temp) 
		{
			*temp = ft_strndup(index + 1, ft_strlen(index + 1));
		}
	}
	else
	{
		nl_str = NULL;
	}
	return (nl_str);
}

char *return_newline(char *str, char **temp, int fd, char *buff)
{
	char *nl_str;
	char *str_copy;
	int ret;

	if (!str)
		return (NULL);
	ret = 1;
	while (!(nl_str = find_newline(str, temp)) && ret > 0)
	{
		//	write(1, "\nwhile\n", 7);
		ret = read(fd, buff, BUFFER_SIZE);
		str_copy = ft_strndup(buff, ret);
		str = ft_strjoin(str, str_copy);
		free(str_copy);
		if (ret == 0)
		{
			*temp = NULL;
			return (str);
		}
	}
	//	printf("nl_str: |%s|\n", nl_str);
	return (nl_str);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	static char *temp;
	char *str;
	int ret;
//		static int i;

//	i += 1;

//	printf("\n----------\n%d\n----------\n", i);
	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	ret = 1;
	if (temp)
	{
		*line = return_newline(temp, &temp, fd, buff);
	}
	else
	{
		ret = read(fd, buff, BUFFER_SIZE);
		str = ft_strndup(buff, ret);
		*line = return_newline(str, &temp, fd, buff);
	}
	if (*line == NULL || **line == '\0')
	{
		printf("!!!!!!!!\n");
		ret = 0;
	}
	if (ret > 0)
		return (1);
	else if (ret == 0)
		return (0);
	else
		return (-1);
}

int main()
{
	char *str;
	int fd;
	//int fd2;
	int ret;

	str = NULL;
	fd = open("no_newline.txt", O_RDONLY);
	//fd2 = open("half_marge_bottom", O_RDONLY);
	while ((ret = get_next_line(fd, &str)))
	{
	//	printf("ret: %d\n", ret);
		printf("*line: |%s|\n", str);
	}
	//while ((ret = get_next_line(fd2, &str)))
	//{
	//	printf("*line: |%s|\n", str);
	//}
	return (0);
}
