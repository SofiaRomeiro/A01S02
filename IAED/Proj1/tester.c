#include <stdio.h>
#include <stdlib.h>

#define GLOBALMAX 51

int readnum(int duration) {
	char n;
	while ((n = getchar()) != EOF && n != '\n' && n != ' ') {
		if (n >= '0' && n <= '9') {
			duration = duration * 10 + (n - '0');
		}
		else {
			printf("Please insert a positive number\n");
			exit(EXIT_FAILURE);
		}
	}
	return duration;
}

/* l [<id> <id> ...] */
/* l 1 3 10 200 */

void readlist(int list[], int maxsize) {

	char c;
	int num=0;

	while ((c=getchar()) != EOF && c != '\n') {
		/* se c for ' ' -> passa a frente*/
		if (c == ' ') {
			
		}
		else {

		} 
			
	}
	
} 

int main() {

	int duration = 0;

	printf("?\n");
	printf("%d", readnum(duration));

	return 0;
}

