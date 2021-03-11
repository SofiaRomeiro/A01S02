#include <stdio.h>

int main () {
	int a, b, m, d = 1, i = 2;
	printf("? \n");
	scanf("%d", &a);
	printf("? \n");
	scanf("%d", &b);
	if ( (a <= 0) || (b <= 0)) {
		printf("Os numeros devem ser inteiros positivos");
	}
	else {
		m = a;
		if (a > b) {
			m = b;
		}
		while (i <= m) {
			if ((a % i == 0) && (b % i == 0)) {
				d = i;
			}
		++i;
		}
		printf("%d e o maior divisor comum entre %d e %d", d, a, b);
	}
	return 0;
}