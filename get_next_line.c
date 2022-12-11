#include "get_next_line.h"
char *get_line(char *str, char **save)
{
    int nl_index;
    char *line;
    char *tmp;

	tmp = NULL;
    nl_index = ft_strchr(str, '\n');
    if (nl_index)
    {
        if (!*save)
        {
            line = ft_strndup(str, nl_index + 1);
        }
        else
        {
            printf("STR:|%s|\n", str);
            printf("SAVE:|%s|\n", *save);
            tmp = ft_strndup(str, nl_index + 1);
            line = ft_strjoin(*save, tmp);
            free(tmp);
        }
        *save = &str[nl_index + 1];
        if (!**save)
            *save = NULL;
    }
    else
        line = ft_strndup(str, ft_strlen(str));
    return (line);

}

char *find_newline(int fd)
{
    char *line;
    char buffer[BUFFER_SIZE + 1];
    char *tmp;
    int ret;

    line = NULL;
    ret = 1;
    while (ret && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret <= 0)
            return (NULL);
        if (!line)
            line = ft_strjoin(buffer, "");
        else
        {
            tmp = line;
            line = ft_strjoin(line, buffer);
            free(tmp);
        }
    }
    return (line);
}

char *get_next_line(int fd)
{
    char check_buffer[1];
    static char *save;
    char **ptr;
    char *line;

    if (fd < 0 || read(fd, check_buffer, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    // printf("SAVE:%s\n", save);
    ptr = &save;
    line = find_newline(fd);
    line = get_line(line, ptr);
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