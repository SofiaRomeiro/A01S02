#include <stdio.h>

typedef struct {
	char name[10];
	int age;
} Cao;

Cao leCao() {
	Cao cao;
	int i;
	char c;
	cao.age = 0;
	printf("name and age?\n");
	for(i=0; i < 9 && (c=getchar()) != EOF && c != '\n' && c != ' '; i++) {
		cao.name[i] = c;		
	}
	cao.name[i] = '\0';	

	while ((c=getchar()) != EOF && c != '\n') {
		if (c >= '0' && c <= '9') {
			cao.age = cao.age * 10 + (c - '0');
			printf("age : %d\n", cao.age);
		} 
	}
	return cao;
}

void escreveCao(Cao cao, int i){
	printf("id cao : %d\nname : %s\nage : %d\n", i, cao.name, cao.age);
} 

int main() {
	int i;
	Cao caes[10];

	for (i=0; i < 3; i++) {
		caes[i] = leCao();
		escreveCao(caes[i], i);
	}

	return 0;
}

	













