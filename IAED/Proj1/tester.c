#include <stdio.h>
#include <stdlib.h>

#define GLOBALMAX 51

int readnum(int duration) {
	char c;
	while ((c = getchar()) != EOF && c != '\n' && c != ' ') {
		if (c >= '0' && c <= '9') {
			duration = duration * 10 + (c - '0');
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
	int id=0, i, idpos=0;

	for (i=0; i < maxsize && (c=getchar()) != EOF && c != '\n'; i++) {
		/* se c for ' ' -> passa a frente, adiciona o id ao array e da clean no id*/
		if (c == ' ') {
			list[idpos++] = id;
			id = 0;			
		}
		else {			
			if (c >= '0' && c <= '9') {
				id = id * 10 + (c - '0');
			}
		} 			
	}
	list[idpos] = id;		
} 

int main() {

	int duration = 0;
	int list[20];

	printf("?\n");
	printf("%d : duration\n", readnum(duration));
	readlist(list, 10000);

	return 0;
}

