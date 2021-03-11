#include <stdio.h>

int main() {
	int a; 
	int b;
	int c;

	printf(" ? \n ");
	scanf("%d %d %d", &a, &b, &c);

	if ( (a < 1) | (b < 1) | (c < 1)) {
		printf("As dimensoes dos lado do triangulo devem ser todas positivas");
	}
	else {
		
		if ( (a + b <= c) | (a + c <= b) | (c + b <= a)) {
			printf("Nao e triangulo");
		}
		else {

			if ((a == b) & (b == c)) {
				printf("O triangulo e equilatero");
			}

			else {

				if ((a == b) | (b == c) | (c == a)) {
					printf("O triangulo e isosceles");
				}

				else {
					printf("O triangulo e escaleno");
				}
			}
		}	
	}
}