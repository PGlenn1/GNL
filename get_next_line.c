#include "get_next_line.h"
char *trim_line(char *line, char **save)
{
    int nl_index;
    char *tmp;
    char *tmp_save;

    tmp = tmp_save = *save;
    nl_index = ft_strchr(*save, '\n');
    if (nl_index)
    {
        *save = &line[nl_index + 1];
        line = ft_strndup(*save, nl_index + 1);
        return (line);
    }
    nl_index = ft_strchr(line, '\n');
    if (nl_index)
    {
        tmp = line;
        *save = &line[nl_index + 1];
        line = ft_strndup(line, nl_index + 1);
        // return (line);
    }
    return (line);
}

char *extract_line(char *line, char *save, char *buffer)
{
    char *tmp;

    tmp = save;
    if (!line)
    {
        if (!save || !*save)
            line = ft_strjoin(buffer, "");
        else
        {
            line = ft_strjoin(save, buffer);
            *save = 0;
        }
    }
    else
        line = ft_strjoin(line, buffer);
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
    while (ret > 0 && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buffer[ret] = '\0';
        line = extract_line(line, save, buffer);
    }
    line = trim_line(line, &save);
    if (!*line)
        return (NULL);
    return (line);
}

// int main()
// {
// int fd;
// char *line;
//
// fd = open("text_files/text", O_RDONLY);
// if (fd < 0)
// return (1);
// line = get_next_line(fd);
// int i = 0;
// while (line)
// {
// printf("\n\nLINE:|%s|\n\n", line);
// line = get_next_line(fd);
// i++;
// }
// printf("\n\nEND LINES\n\n");
// return (0);
// }