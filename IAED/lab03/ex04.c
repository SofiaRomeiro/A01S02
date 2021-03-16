#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
/*
#define DIM 10
#define FINAL 10

int main() {
	int c, i;
	int getchar();
	char s[DIM] = "";
	
	for (i = 0; i < DIM - 1 && (c = getchar()) != EOF && c != '\n' && c != '\0' ; i++) {
		s[i]=c;
	}

	for (i = 0; i < DIM - 1; i++) {
	
		if (s[i] == 0) {
		
			printf("ola\n");
		}
	}
	
	printf("%s \n", s);
	return 0;
} */

int main() {
	char c;

	printf("write some shit, EOF when done");
	while (c != '\0') {
		c = getchar();
		printf("it is: ");
		putchar(c);
		printf("\n");	
	}

}

