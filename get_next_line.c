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

int	get_line(char **temp, int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	char *str;
	char *str_copy;
	int ret;

//	printf("GNL\n");
	str = NULL;
	ret = 1;
	while (!(*line = find_newline(str, temp)) && ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		if (!str)
			str = ft_strndup(buff, ret);
		else
		{
			str_copy = ft_strndup(buff, ret);
			str = ft_strjoin(str, str_copy);
			free(str_copy);
		}
//		printf("ret: %d\n", ret);
		if (ret == 0)
		{
//			printf("ret == 0\n");
			*line = str;
			break;
		}
	}
	return (ret);
}

int	get_next_line(int fd, char **line)
{
	static char *temp;
	int ret;
	//		static int i;

	//	i += 1;

	//	printf("\n----------\n%d\n----------\n", i);
	if (fd < 0 || !line)
		return (-1);
	ret = get_line(&temp, fd, line);
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
//	int fd2;
	int ret;

	str = NULL;
	fd = open("ku", O_RDONLY);
	//	fd2 = open("half_marge_bottom", O_RDONLY);
	while ((ret = get_next_line(fd, &str)))
	{
		//	printf("ret: %d\n", ret);
		printf("*line: |%s\n", str);
	}
	printf("*last line: |%s\n", str);
	//	while ((ret = get_next_line(fd2, &str)))
	//	{
	//		printf("*line: |%s\n", str);
	//	}
	return (0);
}
