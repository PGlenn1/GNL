#include "get_next_line.h"

char *find_newline(char *str)
{
	char *str2;
	char *newline;

	if ((newline = ft_strchr(str, '\n')))
	{
		str2 = newline;
	}
	else
		str2 = str;
	printf("\nstr: %s\n", str2);
	return (str2);
}

int	main()
{
	char buff[BUFFER_SIZE + 1];
	int fd;
	int ret;
	static char *str;
	int count;

	fd = open("prout", O_RDONLY);
	str = NULL;
	count = 10;
	while ((ret = read(fd, buff, count)))
	{
		if (!str)
		{
			str = find_newline(ft_strndup(buff, count));
		}
		else
		{
			str = find_newline(ft_strjoin(str, buff));	
		}
		printf("\nbuff:%s\n", buff);
		//printf("\nstr:%s\n", str);
	}
	return (0);
}
