#include <stdio.h>

int main() {

	float media, n, i = 0, num, sum = 0;

	printf(" number of elements ?\n");
	scanf("%f", &n);

	while (i != n) {
		printf("number ?\n");
		scanf("%f", &num);
		sum = sum + num;
		++i;
	}
	media = sum / n;

	printf("%.2f : media\n", media);

	return 0;
}