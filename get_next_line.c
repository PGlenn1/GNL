#include "get_next_line.h"

char *find_newline(char *str, char **temp, int ret)
{
	(void)ret;
	char *nl_str;
	char *index;

	if (!str)
		return (NULL);
	index = ft_strchr(str, '\n');
	if (index)
	{
		nl_str = ft_substr(str, 0, index - str);
	//	printf("ku\n");
		if (temp) 
		{
	//		printf("yo\n");
			*temp = ft_strndup(index + 1, ft_strlen(index + 1));
	//		printf("prout\n");
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
//	printf("return nl called\n");
	while (!(nl_str = find_newline(str, temp, ret)) && ret > 0)
	{
	//	printf("while nl_str = NULL\n");
		ret = read(fd, buff, BUFFER_SIZE);
		str_copy = ft_strndup(buff, ret);
		str = ft_strjoin(str, str_copy);
		free(str_copy);
		//printf("ret: %d\n", ret);
		if (ret == 0)
		{
			nl_str = str;
			//write(1, "a", 1);
			//printf("nique\n");
			//printf("str in while |%s|\n", str);
			//printf("nl_str in while: |%s|\n", nl_str);
		}
	}
	//printf("nl_str returned: %s\n", nl_str);
	return (nl_str);
}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	static char *temp;
	char *str;
	int ret;
	static int i;

	i += 1;

//	printf("\n---------\n%d\n---------\n", i);

	if (fd < 0 || !line)
		return (-1);
	ret = 1;
	if (temp)
	{
		*line = return_newline(temp, &temp, fd, buff);
		if (*line == NULL)
		{
			ret = 0;
		}
	}
	else
	{
		ret = read(fd, buff, BUFFER_SIZE);
		str = ft_strndup(buff, ret);
		*line = return_newline(str, &temp, fd, buff);
	}
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
//	int ret;
//
//	str = NULL;
//	fd = open("alphabet", O_RDONLY);
//	while ((ret = get_next_line(fd, &str)))
//	{
//		printf("\n*line: |%s|\n\n", str);
//	}
//	return (0);
//}
