#include "get_next_line.h"

char *find_newline(char *str, char **temp)
{
	char *nl_str;
	char *index;

	if (!str)
		return (NULL);
	//printf("\nfind_newline called\nstr: |%s|\n", str);
	index = ft_strchr(str, '\n');
	if (index)
	{
		write(1, "\n!newline!\n", 12);
		//printf("!newline_found!\n");
		nl_str = ft_substr(str, 0, index + 1 - str);
		write(1, nl_str, ft_strlen(nl_str));
		if (temp) 
		{
			if (*temp)
				free (*temp);
			*temp = ft_strdup(index + 1);
			write(1, "\ntemp:\n", 7);
			write(1, *temp, ft_strlen(*temp));
			write(1, "\n", 1);
			//printf("NL found temp: |%s|\n", *temp);
		}
	}
	else
	{
//		printf("no newline found\n");
		nl_str = NULL;
	}
	//printf("find nl_str: |%s|\n", nl_str);
	return (nl_str);
}

char *return_newline(char *str, char **temp, int fd, char *buff)
{
	char *nl_str;
	char *str_copy;
	int ret;

//	printf("\nreturn newline called\n");
	if (!str)
		return (NULL);
	ret = 1;
	while (!(nl_str = find_newline(str, temp)) && ret > 0)
	{
	//	printf("while null\n");
		ret = read(fd, buff, BUFFER_SIZE);
		str_copy = ft_strndup(buff, ret);
		str = ft_strjoin(str, str_copy);
		free(str_copy);
	}
//	printf(" after while ret:%d\n", ret);
	//printf("return nl_str: |%s|", nl_str);
	return (nl_str);

}

int	get_next_line(int fd, char **line)
{
	char buff[BUFFER_SIZE + 1];
	static char *temp;
	char *str;
	int ret;
	static int i;

//	printf("---------\n%d\n---------\n", i);
	i += 1;

	//printf("\nGNL temp: |%s|\n", temp);
	if (temp)
	{
		write(1, temp, ft_strlen(temp));
	//	write(1, "temp\n", 5);
		*line = return_newline(temp, &temp, fd, buff);
	//	printf("\n\nif temp *line: |%s|\n", *line);
		if (*line == NULL)
		{
			ret = 0;
		}
	}
	else
	{
	//	write(1, "no temp\n", 8);
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

int main()
{
	char *str;
	int fd;
	int ret;

	str = NULL;
	fd = open("prout", O_RDONLY);
	while ((ret = get_next_line(fd, &str)))
	{
		printf("\n*line: |%s|\nret = %d\n\n", str, ret);
	}
	return (0);
}
