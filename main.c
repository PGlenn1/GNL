#include "get_next_line.h"

char	*find_newline(char *str)
{
	int i;
	static char *stock;

	i = 0;
	stock = "";
	while (str[i])
	{
		if (str[i] == '\n')
		{
			stock = ft_strjoin(stock, str);
			return (stock);
		}
		i++;
	}
	return (str);
}

int	main()
{
	int fd;
	int ret;
	char buff[BUFFER_SIZE + 1];
	//	char *str;

	fd = open("prout", O_RDONLY);
	while ((ret = read(fd, buff, 10) > 0))
	{
		
	}
	//	printf("str: %s\n", str);
	return (0);
	:x

}
