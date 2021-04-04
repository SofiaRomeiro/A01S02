#include <stdio.h>
#include <string.h>

typedef struct {
	char firstname[10];
	char surname[10];
} name;

typedef struct {
	int id;
	name name[10];
	int age;
} Cao;



Cao leCao() {
	Cao cao;
	int i;
	char c;
	int firstname = 0;
	int num = 0;
	cao.age = 0;

	printf("name surname and age?\n");
	if (!firstname && !num) {
		for(i=0; i < 9 && (c=getchar()) != EOF &&c != ' '; i++) {
			cao.name->firstname[i] = c;		
		}
		firstname = 1;
		cao.name->firstname[i] = '\0';
	}
	else if (firstname && !num) {

	for (i=0; i<9 && (c=getchar()) != EOF && c != '\n' && c != ' '; i++) {
		cao.name->surname[i] = c;		
	}
	cao.name->surname[i] = '\0';
	num = 1;
	}
	else{
		while ((c=getchar()) != EOF && c != '\n') {
			if (c >= '0' && c <= '9') {
				cao.age = cao.age * 10 + (c - '0');
			} 
		}
	}
	
	cao.id = cao.id + 1;
	return cao;
}

void escreveCao(Cao cao){
	printf("id cao : %d\nname : %s\nsurname : %s\nage : %d\n", cao.id, cao.name->firstname, cao.name->firstname, cao.age);
} 

int main() {
	int i;
	Cao caes[3];

	for (i=0; i < 3; i++) {
		caes[i] = leCao();
		escreveCao(caes[i]);
	}

	return 0;
} 


	














