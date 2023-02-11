#include "get_next_line.h"

int main()
{
    int file_d[4];
    int fd;
    char *line;
    // fd = open("text_files/text", O_RDONLY);

    file_d[3] = open("gnlTester/files/nl", O_RDONLY);
    file_d[0] = open("gnlTester/files/41_with_nl", O_RDONLY);
    file_d[1] = open("gnlTester/files/42_with_nl", O_RDONLY);
    file_d[2] = open("gnlTester/files/43_with_nl", O_RDONLY);

    // fd = open("gnlTester/files/nl", O_RDONLY);
    // fd = open("gnlTester/files/41_with_nl", O_RDONLY);
    // fd = open("gnlTester/files/42_with_nl", O_RDONLY);
    // fd = open("gnlTester/files/43_with_nl", O_RDONLY);

    fd = open("gnlTester/files/multiple_nlx5", O_RDONLY);
    // fd = open("gnlTester/files/multiple_line_no_nl", O_RDONLY);
    // fd = open("gnlTester/files/multiple_line_with_nl", O_RDONLY);
    // fd = open("gnlTester/files/big_line_with_nl", O_RDONLY);

    // fd = open("gnlTester/files/alternate_line_nl_no_nl", O_RDONLY);
    // fd = open("gnlTester/files/alternate_line_nl_with_nl", O_RDONLY);

    // if (fd < 0)
    // {
    //     printf("DEBUG INVALID FILE\n");
    //     return (1);
    // }

    // printf("\n#1res|%s|\nexpected|%s|\n\n", get_next_line(1000), NULL);
    // printf("\n#2res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[0]), "0123456789012345678901234567890123456789\n");
    // free(line);
    // printf("\n\n");

    // printf("\n#3res|%s|\n\nexpected|%s|\n\n", get_next_line(1001), NULL);
    // printf("\n#4res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[1]), "01234567890123456789012345678901234567890");

    // free(line);
    // printf("\n\n");
    // printf("\n#5res|%s|\n\nexpected|%s|\n\n", get_next_line(1002), NULL);
    // printf("\n#6res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[2]), "012345678901234567890123456789012345678901");

    // free(line);
    // printf("\n\n");
    // printf("\n#7res|%s|\n\nexpected|%s|\n\n", get_next_line(1003), NULL);
    // printf("\n#8res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[0]), "0");

    // free(line);
    // printf("\n\n");
    // printf("\n#9res|%s|\n\nexpected|%s|\n\n", get_next_line(1004), NULL);
    // printf("\n#10res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[1]), "1");

    // free(line);
    // printf("\n\n");
    // printf("\n#11res|%s|\n\nexpected|%s|\n\n", get_next_line(1005), NULL);
    // printf("\n#12res|%s|\n\nexpected|%s|\n\n", line = get_next_line(file_d[2]), "2");

    // free(line);
    // printf("\n\n");
    // printf("\n#13res|%s|\n\nexpected|%s|\n\n", get_next_line(file_d[0]), NULL);
    // printf("\n#14res|%s|\n\nexpected|%s|\n\n", get_next_line(file_d[1]), NULL);
    // printf("\n#15res|%s|\n\nexpected|%s|\n\n", get_next_line(file_d[2]), NULL);

    // printf("\n\n");
    line = get_next_line(fd);
    printf("\n\nLINE:|%s|\n\n", line);
    while (line)
    {
        free(line);
        line = get_next_line(fd);
        printf("\n\nLINE:|%s|\n\n", line);
    }
    free(line);
    return (0);
}