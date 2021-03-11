#include <stdio.h>

int main() {

	float n, max, min;

	printf("? \nchar to finish \n");
	scanf("%f", &n);
	max = n;
	min = n;

	while (printf("? \nchar to finish \n"), scanf("%f", &n) == 1 ) {
		if (n > max) {
			max = n;
		}
		else if (n < min) {
			min = n;
		}		
	}	

	printf("min: %f, max: %f\n", min, max);
	return 0;
}