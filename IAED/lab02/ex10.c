#include <stdio.h>

int main() {

	int n;
	float h, m, s;

	printf("segundos?\n");
	scanf("%d", &n);

	h = n/3600;
	m = (n - (3600 * h)) / 60;
	s = (n - (3600 * h)) - (m * 60);

	printf("%f:%f:%f", h, m, s)
	return 0;
}