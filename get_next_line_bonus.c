#include "get_next_line_bonus.h"

int find_fd(struct fd_data *fd_array, int fd)
{
    int i = 0;

    if (fd < 0)
        return (-1);
    while (i < ARRAY_SIZE && fd_array[i].fd != fd)
    {
        if (fd_array[i].fd == 0)
        {
            fd_array[i].fd = fd;
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
    static struct fd_data fd_array[ARRAY_SIZE];
    int fd_index;
    int ret;

    fd_index = find_fd(fd_array, fd);
    if (fd < 0 || fd_index < 0 || read(fd, check_buffer, 0) < 0 || BUFFER_SIZE == 0)
        return (NULL);
    ret = 1;
    line = NULL;
    if (ft_strchr(fd_array[fd_index].save, '\n'))
        return (find_nl(fd_array[fd_index].save, &(fd_array[fd_index].save)));
    while (ret > 0 && !ft_strchr(line, '\n'))
    {
        ret = read(fd, buffer, BUFFER_SIZE);
        if (ret < 0)
            return (NULL);
        buffer[ret] = '\0';
        line = join_line(line, &(fd_array[fd_index].save), buffer);
        if (!line)
            return (NULL);
    }
    return (find_nl(line, &(fd_array[fd_index].save)));
}

// int main()
// {
//     int fd;
//     int fd2;
//     char *line;
//     char *line2;
//     char *tmp;

//     fd = open("text_files/text", O_RDONLY);
//     fd2 = open("text_files/multi_fd", O_RDONLY);
//     // printf("fd:%d | fd2:%d\n", fd, fd2);
//     if (fd < 0 || fd2 < 0)
//         return (1);
//     line = get_next_line(fd);
//     printf("\n\nLINE1:|%s|\n\n", line);
//     line2 = get_next_line(fd2);
//     printf("\n\nLINE2:|%s|\n\n", line2);
//     tmp = line;
//     int i = 0;
//     while (line || line2)
//     {
//         free(line);
//         line = get_next_line(fd);
//         printf("\n\nLINE:|%s|\n\n", line);
//         free(line2);
//         line2 = get_next_line(fd2);
//         printf("\n\nLINE2:|%s|\n\n", line2);
//         i++;
//     }
//     // printf("\n\nLINE:|%s|\n\n", line);
//     // printf("\n\nLINE:|%s|\n\n", line2);
//     free(line);
//     free(line2);
//     // printf("\n\nEND LINES\n\n");
//     return (0);
// }
