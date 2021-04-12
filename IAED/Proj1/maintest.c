#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int less(int v, int j_time) {

	if (v < j_time) {
		return 1;
	}	 
	return 0;

}

void insertion(int a[], int l, int r) {
	int i,j;
	for (i = l+1; i <= r; i++) {
		int v = a[i];
		j = i-1;
			while ( j>=l && less(v ,a[j])) {
				a[j+1] = a[j];
				j--;
			}
		a[j+1] = v;
	}
}

int main() {

	int numbers[10];
	int max = 9, min = 0;
	int i;

	for (i=0; i <= max; i++) {
		numbers[i] = (int) 100 * (1.0*rand()/RAND_MAX);
		if (i < max) {
			printf("%d ", numbers[i]);
		}
		else {
			printf("%d\n", numbers[i]);
		}
	}	

	insertion(numbers, min, max);

	for (i=0; i <= max; i++) {
		if (i < max) {
			printf("%d ", numbers[i]);
		}
		else {
			printf("%d\n", numbers[i]);
		}
	}

}

