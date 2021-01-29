#include <stdio.h>
#include <stdlib.h>

void my_fn(char *tmp) {
	tmp = malloc(3);
}

int main() {
	char *tmp = NULL;

	printf("before : %p\n", tmp);
	my_fn(tmp);
	printf("after : %p\n", tmp);
	return (0);
}
