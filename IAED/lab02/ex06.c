#include <stdio.h>

int main () {

	int a, b, c;
	printf("? \n");
	scanf("%d", &a);
	printf("? \n");
	scanf("%d", &b);
	printf("? \n");
	scanf("%d", &c);

	if ( (a > b) && (a > c)) {
		printf("%d e o maior numero", a);
	}

	else if ((b > c) && (b > a)) {
		printf("%d e o maior numero", b);
	}
	else {
		printf("%d e o maior numero", c);
	}
	return 0;
}