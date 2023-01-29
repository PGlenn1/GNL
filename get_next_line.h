#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE 1024
#endif

typedef struct fd_data
{
	int fd;
	char *save;
} fd_data;

int ft_strchr(char *s, int c);
char *ft_strjoin(char *s1, char *s2);
unsigned int ft_strlen(char *str);
char *ft_strndup(char *s1, unsigned int n);
char *get_next_line(int fd);