#include "get_next_line.h"
unsigned int find_fd(int fd, fd_data_t fd_array[ARRAY_SIZE])
{
    unsigned int i;

    i = 0;
    while (i < ARRAY_SIZE)
    {
        if (fd_array[i].fd == fd)
            return (i);
        i++;
    }
    if (i == ARRAY_SIZE)
    {
        i = 0;
        while (fd_array[i].fd && i < ARRAY_SIZE)
            i++;
        if (fd_array[i].fd == 0)
            fd_array[i].fd = fd;
    }
    return (i);
}

char *check_rem(char *line, char **rem)
{
    unsigned int nl_index;
    char *tmp;

    // rem ptr sur ptr
    nl_index = ft_strchr(*rem, '\n');
    if (nl_index)
    {
        tmp = *rem;
        // printf("rem:%s\n", tmp);
        line = ft_strndup(tmp, nl_index + 1);
        *rem = ft_strndup(&tmp[nl_index + 1], ft_strlen(&tmp[nl_index + 1]));
        printf("rem:%s\n", *rem);
        free(tmp);
        return (line);
    }
    return (0);
}

char **read_newline(int fd, char **rem, char *buf)
{
    int ret;
    char *tmp;

    tmp = *rem;
    ret = 1;
    while (ret && !ft_strchr(buf, '\n'))
    {
        ret = read(fd, buf, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buf[ret] = 0;
        if (!*rem)
            *rem = ft_strjoin(buf, "");
        else
        {
            // printf("rem found:%s\n", *rem);
            *rem = ft_strjoin(*rem, buf);
            free(tmp);
        }
    }
    // printf("rem newline:%s\n", *rem);
    // if (ft_strchr(buf, '\n'))
    // {
    //     printf("YES\n");
    // }
    return (rem);
}

char *get_newline(int fd, char *line, char **rem, char *buf)
{
    line = check_rem(line, rem);
    if (line)
        return (line);
    rem = read_newline(fd, rem, buf);
    if (ft_strchr(*rem, '\n'))
        return (get_newline(fd, line, rem, buf));
    return (line);
}

char *get_next_line(int fd)
{
    char *line;
    char buff[1];
    static fd_data_t fd_array[ARRAY_SIZE];
    char buf[BUFFER_SIZE + 1];
    unsigned int array_index;

    if (fd < 0 || read(fd, buff, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    line = NULL;
    array_index = find_fd(fd, fd_array);
    return (get_newline(fd, line, &fd_array[array_index].rem, buf));
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
        printf("LINE %s", line);
        line = get_next_line(fd);
    }
    return (0);
}