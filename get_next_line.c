#include "get_next_line.h"

char *trim_line(char *line, char **save)
{
    int nl_index;
    char *line_tmp;
    char *save_tmp;

    line_tmp = line;
    save_tmp = *save;
    nl_index = ft_strchr(*save, '\n');
    if (nl_index)
    {
        *save = ft_strndup(&(*save[nl_index + 1]), ft_strlen(&(*save[nl_index + 1])));
        line = ft_strndup(*save, nl_index + 1);
        free(save_tmp);
        return (line);
    }
    nl_index = ft_strchr(line, '\n');
    if (nl_index || *line == '\n')
    {
        *save = ft_strndup(&line[nl_index + 1], ft_strlen(&line[nl_index + 1]));
        line = ft_strndup(line, nl_index + 1);
        free(save_tmp);
        free(line_tmp);
    }
    return (line);
}

char *extract_line(char *line, char *save, char *buffer)
{
    char *line_tmp;

    line_tmp = line;
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
    {
        line = ft_strjoin(line, buffer);
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
    {
        free(line);
        return (NULL);
    }
    return (line);
}

// int main()
// {
//     int fd;
//     char *line;
//     char *tmp;

//     fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
//     if (fd < 0)
//         return (1);
//     line = get_next_line(fd);
//     tmp = line;
//     int i = 0;
//     while (line)
//     {
//         printf("\n\nLINE:|%s|\n\n", line);
//         free(line);
//         line = get_next_line(fd);
//         i++;
//     }

//     printf("\n\nLINE:|%s|\n\n", line);
//     free(line);
//     printf("\n\nEND LINES\n\n");
//     return (0);
// }
