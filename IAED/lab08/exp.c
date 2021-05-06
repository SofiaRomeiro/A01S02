#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *f4(char *x) {

	char *y = x-1;
	int i = 2;

	while (*++y)
		if (*y == 'Y')
			*(y+i) = 'y';
		else y[0]++;
	return x;
}

int main() {

	char *x = malloc(strlen("xYyYxY")+1);
	strcpy(x, "xYyYxY");
	f4(x);
	printf("%s\n", x);

	return 0;
}