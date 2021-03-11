#include <stdio.h>


int main() {
	int sum = 0, a = 1, x;
	printf("? \nchar to finish \n");
	x = scanf("%d", &a);
	while (x == 1) { /* qlqr expressao pode estar no while desde que seja int, significa q conseguiu ler o numero (== 1) */
		sum += a;
		printf("? \nchar to finish \n");
		x = scanf("%d", &a);
	}
	printf("%d \n", sum);
	return 0;
}  

/*
	int sum = 0, a = 1, x;
	printf("? \n");
	x = scanf("%d", &a);
	while ( printf("? \n"), scanf("%d", &a)== 1) { 
		sum += a;
	}
	printf("%d \n", sum);
	return 0;
*/
