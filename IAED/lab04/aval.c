#include <stdio.h>


/* funcao variancia, n --> size */

double variance(char vec[], int n) {

	double mean=0, variance=0;
	int i;

	/* media */ 
	for (i=0; i < n; i++) {
		mean += vec[i];
	}
	mean /= n;

	for (i=0; i < n; i++) {
		variance += ((vec[i] - mean)*(vec[i] - mean));
	}
	variance /= (n-1);

	return variance;
}

int main() {

	int n, i;
	printf("n ?");
	scanf("%d", &n);

	char vec[n];
	for ()

	printf("%f", variance(vec, n));

	return 0;
}