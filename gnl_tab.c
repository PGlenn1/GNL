#include "get_next_line.h"

char *find_newline(char *str, struct s_list *t_list)
{
	char *nl_str;
	char *newline;

	nl_str = NULL;
	if ((newline = ft_strchr(t_list->temp, '\n')))
		nl_str = ft_substr(t_list->temp, 0, newline - t_list->temp);
	else if ((newline = ft_strchr(str, '\n')))
		nl_str = ft_substr(str, 0, newline - str);
	if (newline)
		t_list->temp = ft_strndup(newline + 1, ft_strlen(newline + 1));
	else
	{
		if (str)
			t_list->temp = str;
	}
	return (nl_str);
}

int	get_line(int fd, char **line, struct s_list *t_list)
{
	int ret;
	char buff[BUFFER_SIZE + 1];
	char *str;

	str = NULL;
	ret = 1;
	while (!(*line = find_newline(str, t_list)))
	{
		if (ret == 0)
		{
			if (t_list->temp)
			{
				*line = t_list->temp;
				t_list->temp = NULL;
			}
			else
				*line = str;
			break;
		}
		if ((ret = read(fd, buff, BUFFER_SIZE)))
		{
			str = ft_strndup(buff, ret);
			if (t_list->temp)
			{
				str = ft_strjoin(t_list->temp, str);
				t_list->temp = NULL;
			}
		}
	}
	return (ret);
}

t_list *make_struct(int fd, char **line)
{
	int i;
	struct s_list t_list;

	t_list.fd = fd;
	t_list.temp = NULL;
	
	return (t_list);
}

t_list *make_tab(int fd, char **line, struct s_list *tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		if (tab[i].fd == fd)
			return (tab);
		i++;
	}
	if (!(tab = malloc(sizeof(struct s_list) * (i + 1))))
		return (NULL); 
	tab[i + 1] = make_tab(fd, line);
	// COPIER TABLEAU DANS NOUVEAU TAB
	return (tab);
}

int	get_next_line(int fd, char **line)
{
	static struct s_list tab[];
	char buff[1];
	int ret;
	int i;

	if (fd < 0 || !line || read(fd, buff, 0) < 0)
		return (-1);
	if (!tab)
	{
		if (!(tab = malloc(sizeof(struct s_list) * 1)
			return (-1);
		tab[0] = make_tab(fd, line);
	}
	else
		tab = stretch_tab(fd, line, tab);
	i = 0;
	while (tab[i++].fd != fd);
	ret = get_line(fd, line, tab[i]);
	if (*line == NULL)
		*line = ft_strndup("", 0);
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
	int tab[];
	int fd;
	int fd2;
	int ret;
	int i;

	i = 0;

	str = NULL;
	fd = open("yes", O_RDONLY);
	fd2 = open("non", O_RDONLY);
	tab[0] = fd;
	tab[1] = fd2;
	while ((ret = get_next_line(tab[i], fd)))
	{
		printf("*line: |%s\n", str);
	}
	return (0);
}
