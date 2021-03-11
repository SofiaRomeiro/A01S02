#include <stdio.h>

int main() {

	int n, i = 1, ndiv = 1;

	printf("numero ?\n");
	scanf("%d", &n);

	while (i != n) {
		if (n % i == 0) {
			++ndiv;
		}
		++i;
	}
	printf("%d tem %d divisores", n, ndiv);
	return 0;
}