#include "get_next_line.h"
unsigned int find_fd(int fd, file_data_t file_data[ARRAY_SIZE])
{
    unsigned int i;

    i = 0;
    while (i < ARRAY_SIZE)
    {
        if (file_data[i].fd == fd)
            return (i);
        i++;
    }
    if (i == ARRAY_SIZE)
    {
        i = 0;
        while (file_data[i].fd && i < ARRAY_SIZE)
            i++;
        if (file_data[i].fd == 0)
            file_data[i].fd = fd;
    }
    return (i);
}

char *check_rem(file_data_t file_data, char *line)
{
    unsigned int nl_index;
    char *tmp;

    // rem ptr sur ptr
    nl_index = ft_strchr(file_data.rem, '\n');
    if (nl_index)
    {
        tmp = file_data.rem;
        // printf("rem:%s\n", tmp);
        line = ft_strndup(tmp, nl_index + 1);
        printf("check line:%s\n", line);
        file_data.rem = ft_strndup(&tmp[nl_index + 1], ft_strlen(&tmp[nl_index + 1]));
        // printf("check rem:%s\n", *rem);
        free(tmp);
        return (line);
    }
    return (0);
}

char *read_newline(file_data_t file_data, char *buf)
{
    int ret;
    char *tmp;

    tmp = file_data.rem;
    ret = 1;
    while (ret && !ft_strchr(buf, '\n'))
    {
        ret = read(file_data.fd, buf, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buf[ret] = 0;
        if (!file_data.rem)
            file_data.rem = ft_strjoin(buf, "");
        else
        {
            // printf("rem found:%s\n", *rem);
            file_data.rem = ft_strjoin(file_data.rem, buf);
            free(tmp);
        }
    }
    // printf("rem newline:%s\n", *rem);
    // if (ft_strchr(buf, '\n'))
    // {
    //     printf("YES\n");
    // }
    return (file_data.rem);
}

char *get_newline(file_data_t file_data, char *line, char *buf)
{
    // printf("rem:%s\n", *rem);
    line = check_rem(file_data, line);
    if (line)
    {
        // printf("LINE TEST:%s\n", line);
        return (line);
    }
    file_data.rem = read_newline(file_data, buf);
    if (ft_strchr(file_data.rem, '\n'))
    {
        // printf("BINGO\n");
        return (get_newline(file_data, line, buf));
    }
    return (line);
}

char *get_next_line(int fd)
{
    char *line;
    char buff[1];
    static file_data_t file_data[ARRAY_SIZE];
    char buf[BUFFER_SIZE + 1];
    unsigned int array_index;

    if (fd < 0 || read(fd, buff, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    line = NULL;
    array_index = find_fd(fd, file_data);
    return (get_newline(file_data[array_index], line, buf));
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