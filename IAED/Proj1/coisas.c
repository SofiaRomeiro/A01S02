#include <stdio.h>
#include <string.h>

void exch(int sort[], int i, int j) {
	int temp;
	temp = sort[i]; 	
	sort[i] = sort[j]; 	
	sort[j] = temp;  
}


int lessL(int v, int a_j) {

	return v < a_j;
}

int partition(int sort[], int l, int r) {
	int i = l-1; 
	int j = r; 
	int v=sort[r];
	while (i < j) { 				
		while (lessL(sort[++i], v));				
		while (lessL(v, sort[--j])) 
			if (j == l) 
				break;
		if (i < j)
			exch(sort, i, j); 
	}
	exch(sort, r, i);
	return i; 
}

void insertion(int a[], int l, int r) {
	int i,j, k;
	int v;
	for (i = l+1; i <= r; i++) {
		for (k=0;k<=r;k++) { printf("%d ", a[k]); }
		printf("\n");
		v = a[i];
		j = i-1;
		while ( j>=l && lessL(v, a[j])) {
			a[j+1] = a[j];
			j--;
		}
	a[j+1] = v;
	}
}

int cenas() {

	return 1 ? strcmp("tadeus", "ola")<0 : 0;
}

int main() {
/*	int a[9];
	int max = 6;
	a[0]=35;
	a[1]=40;
	a[2]=4;
	a[3]=6;
	a[4]=17;
	a[5]=21;
	a[6]=34; */

/*	insertion(a, 0, max); */

	printf("%d\n",cenas());

	return 0;

}