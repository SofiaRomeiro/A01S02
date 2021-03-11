#include <stdio.h>

int main() {

	int d = 0;
	int n;
	int i = 2;
	printf("? \n");
	scanf("%d", &n);
	if (n > 0) {
		while (i <= n / 2) {
			if (n % i == 0) {
				printf("%d e divisivel por %d \n", n, i);
				++d;
			}
			++i;
		}
		if (d == 0) {
			printf("%d e primo. \n", n);			
		}
	}
	return 0;
}