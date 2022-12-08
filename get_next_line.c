#include "get_next_line.h"
char *get_line(char *str, char *save)
{
    int nl_index;   
    char *line;
    char *new_save;
    char *tmp;

	printf("str:%s\n", str);
    nl_index = ft_strchr(str, '\n');
    tmp = NULL;
    if (nl_index)
    {
        printf("test\n");
        tmp = save;
        ne
        line = ft_strndup(save, ft_strchr(save, '\n'));
        printf("debuuuuuuuuuuug\n");
        save = &save[ft_strchr(save, '\n') + 1];
        printf("save:%s\n", save);
        free(tmp);
    }
    return (line);

}

char *find_newline(int fd)
{
    char *line;
    static char buffer[BUFFER_SIZE + 1];
    char *tmp;
    int ret;

    line = NULL;
    ret = 1;
    while (ret && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        if (!line)
        {
            line = ft_strjoin(buffer, "");
        }
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
    char *line;

    if (fd < 0 || read(fd, check_buffer, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    line = NULL;
    if (ft_strchr(save, '\n'))
        return (get_line(save, save));
    line = find_newline(fd);
    if (ft_strchr(line, '\n'))
    {
        return (get_line(line, save));
    }
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
    while (line)
    {
        printf("LINE %s\n", line);
        line = get_next_line(fd);
    }
    return (0);
}