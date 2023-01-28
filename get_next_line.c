#include "get_next_line.h"

char *find_nl(char *str, char **save)
{
    char *str_tmp;
    unsigned int nl_index;

    str_tmp = str;
    nl_index = ft_strchr(str, '\n');
    if (nl_index || *str == '\n')
    {
        str = ft_strndup(str_tmp, nl_index + 1);
        if (!str)
            return (NULL);
        *save = ft_strndup(&str_tmp[nl_index + 1], ft_strlen(&str_tmp[nl_index + 1]));
        if (!*save)
            return (NULL);
        free(str_tmp);
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
        **save = 0;
        free(*save);
        *save = NULL;
    }
    return (line);
}

char *join_line(char *line, char **save, char *buffer)
{
    char *line_tmp;

    line_tmp = line;
    if (!line)
        line = create_line(save, buffer);
    else
    {
        line = ft_strjoin(line_tmp, buffer);
        if (!line)
            return (NULL);
        free(line_tmp);
    }
    return (line);
}

char *get_next_line(int fd)
{
    char buffer[BUFFER_SIZE + 1];
    char check_buffer[1];
    char *line;
    static char *save;
    int ret;

    if (fd < 0 || read(fd, check_buffer, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    ret = 1;
    line = NULL;
    if (ft_strchr(save, '\n'))
        return (find_nl(save, &save));
    while (ret > 0 && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buffer[ret] = '\0';
        line = join_line(line, &save, buffer);
        if (!line)
            return (NULL);
    }
    return (find_nl(line, &save));
}

int main()
{
    int fd;
    char *line;
    char *tmp;

    // fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
    fd = open("text_files/text", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    tmp = line;
    int i = 0;
    while (line)
    {
        // printf("\n\nLINE:|%p|\n\n", line);
        printf("\n\nLINE:|%s|\n\n", line);
        free(line);
        line = get_next_line(fd);
        i++;
    }

    printf("\n\nLINE:|%s|\n\n", line);
    free(line);
    // printf("\n\nEND LINES\n\n");
    return (0);
}
