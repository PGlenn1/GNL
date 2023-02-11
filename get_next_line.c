#include "get_next_line.h"

int ffd(struct fd_data *ar, int fd)
{
    int i;

    if (fd < 0)
        return (-1);
    i = 0;
    while (i < ARRAY_SIZE && ar[i].fd != fd)
    {
        if (ar[i].fd == 0)
        {
            ar[i].fd = fd;
            return (i);
        }
        i++;
    }
    if (i == ARRAY_SIZE)
        return (-1);
    return (i);
}

char *find_nl(char *str, char **save)
{
    char *tmp;
    unsigned int index;

    tmp = str;
    index = ft_strchr(str, '\n');
    if (index || *str == '\n')
    {
        str = ft_strndup(tmp, index + 1);
        if (!str)
            return (NULL);
        if (tmp[index + 1] || *tmp == '\n')
        {
            *save = ft_strndup(&tmp[index + 1], ft_strlen(&tmp[index + 1]));
            if (!*save)
                return (NULL);
        }
        else
            *save = NULL;
        free(tmp);
    }
    return (str);
}

char *create_line(char **save, char *buffer)
{
    char *line;

    line = NULL;
    if (!*save || !**save)
    {
        if (*buffer)
            line = ft_strjoin(buffer, "");
    }
    else
    {
        line = ft_strjoin(*save, buffer);
        if (!line)
            return (NULL);
        free(*save);
        *save = NULL;
    }
    return (line);
}

char *join_line(char *line, char **save, char *buffer)
{
    char *tmp;

    tmp = line;
    if (!line)
        line = create_line(save, buffer);
    else
    {
        line = ft_strjoin(tmp, buffer);
        if (!line)
            return (NULL);
        free(tmp);
    }
    return (line);
}

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    char check[1];
    char *line;
    static struct fd_data ar[ARRAY_SIZE];
    int ret;

    if (fd < 0 || ffd(ar, fd) < 0 || read(fd, check, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    ret = 1;
    line = NULL;
    if (ft_strchr(ar[ffd(ar, fd)].save, '\n'))
        return (find_nl(ar[ffd(ar, fd)].save, &(ar[ffd(ar, fd)].save)));
    while (ret > 0 && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buffer[ret] = '\0';
        line = join_line(line, &(ar[ffd(ar, fd)].save), buffer);
        if (!line)
            return (NULL);
    }
    return (find_nl(line, &(ar[ffd(ar, fd)].save)));
}
