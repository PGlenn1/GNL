#include "get_next_line.h"
char *trim_line(char **line, char **save)
{
    int nl_index;
    char *tmp;

    tmp = NULL;
    nl_index = ft_strchr(*line, '\n');
    if (nl_index)
    {
        tmp = *line;
        *save = &(*line[nl_index + 1]);
        *line = ft_strndup(*line, nl_index + 1);
        free(tmp);
    }
    return (*line);
}

char *extract_line(char **line, char **save, char *buffer)
{
    char *tmp;

    tmp = NULL;
    if (!*line)
    {
        if (!*save)
            *line = ft_strjoin(buffer, "");
        else
        {
            tmp = *save;
            *line = ft_strjoin(*save, buffer);
            // free(*save);
            *save = NULL;
        }
    }
    else
    {
        tmp = *line;
        *line = ft_strjoin(*line, buffer);
        // free(tmp);
    }
    return (*line);
}

char *find_newline(int fd, char **line, char **save)
{
    char buffer[BUFFER_SIZE + 1];
    int ret;

    ret = 1;
    while (ret && !ft_strchr(*line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret <= 0)
            return (NULL);
        *line = extract_line(line, save, buffer);
    }
    *line = trim_line(line, save);
    return (*line);
}

char *get_next_line(int fd)
{
    char check_buffer[1];
    static char *save;
    char *line;

    if (fd < 0 || read(fd, check_buffer, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    // printf("SAVE:%s\n", save);
    line = find_newline(fd, &line, &save);
    return (line);
}

int main()
{
    int fd;
    char *line;

    fd = open("text_files/text", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    // int i = 0;
    while (line)
    {
        printf("LINE:%s\n", line);
        line = get_next_line(fd);
        // i++;
    }
    // printf("\n\nEND LINES\n\n");
    return (0);
}