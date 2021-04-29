#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *f4(char *x) {

	char *y = x;
	int i = 0;

	while (y[i]) {
		if ((*y)-- == 'Y') {
			y[0] = 'y';
		}
		else {
			y += 1;
		}
	}
	return x;
}

int main() {

	char *x = malloc(strlen("xYyYzY")+1);
	strcpy(x, "xYyYzY");
	f4(x);
	printf("%s\n", x);

	return 0;
}