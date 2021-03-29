#include <stdio.h>
#include <stdlib.h>

/* max value for an identifier = 1000 */
#define IDENTIFIER 10000
/* max username len =  */
#define USERNAME 20
/* max tasks' description len = 50 */
#define DESCFORTASK 50
/* max activities' description len = 20 */
#define DESCFORACTIV 20


void displayMenu();
int readNum();
void readSentence(char sentence[], int maxsize);
void readList(int list[], int maxsize);
void newTask();
void tasksList(int ids[]);

int main() {

	int quit = 0, duration = 0;
	char command;
	char description[DESCFORTASK + 1];
	int ids[IDENTIFIER+2];
	
	while ( !quit ) {
		displayMenu();
		command = getchar();

		switch (command) {
			case 't':
				/* New Task */
				/* IN : t <duration> <description> */
				getchar();
				duration = readNum();
				readSentence(description, DESCFORTASK);
				newTask(duration, description);
				break;

			case 'l':
				/* tasks list
				taskslist(); */
				getchar();
				readList(ids, IDENTIFIER);
				tasksList(ids);
				break;

			case 'n':
				/* time adder 
				timeadder(); */
				break;

			case 'u':
				/* add new user or new list of users 
				newuser(); */
				break;

			case 'm':
				/* move task from one activitie to another
				movetask(); */
				break;

			case 'd':
				/* lists all tasks in one activitie 
				alltaskslist(); */
				break;

			case 'a':
				/* add new activitie or list all activities 
				addactivitie(); */
				break;
			
			case 'q':
				quit = 1;
				break;
			
			default:
				printf("Error : Command Not Found");
				exit(EXIT_FAILURE);
				break;
		}
	}
	return 0;
}

void displayMenu() {
	printf("\nComando \t Acao\n");
	printf("\n");	
	printf(" t \t Adiciona uma nova tarefa ao sistema\n");
	printf(" l \t Lista as tarefas\n");
	printf(" n \t Avanca o tempo do sistema\n");
	printf(" u \t Adiciona um utilizador ou lista todos os utilizadores\n");
	printf(" m \t Move uma tarefa de uma atividade para outra\n");
	printf(" d \t Lista todas as tarefas que estejam numa dada atividade\n");
	printf(" a \t Adiciona uma atividade ou lista todas as atividades\n");
	printf(" q \t Termina o programa\n");
	printf("\n");
}

int readNum() {
	int num = 0, reading = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n' && (c != ' ' || reading == 0)) {
		if (c >= '0' && c <= '9') {
			num = num * 10 + (c - '0');
			reading = 1;
		}

		else if (c == ' ' && !reading){
			continue;
		}

		else {
			printf("Please insert a positive number\n");
			exit(EXIT_FAILURE);
		}
	}
	return num;
}

void readSentence(char sentence[], int maxsize) {
	int i, j,n=0;
	char temporary[DESCFORTASK];
	char c;	
	
	for(i=0; i < (maxsize) && (c=getchar()) != EOF && c != '\n'; i++) {
		temporary[i] = c;		
	}

	for (j=0; j < i; j++){
		if (temporary[j] == ' ') {
			continue;
		}
		else {
			sentence[n++] = temporary[j]; 
		}
	}
	sentence[n] = '\0';
}

void readList(int list[], int maxsize) {
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
	list[idpos+1] = '\0';		
}

void newTask(int duration, char sentence[]) {

	printf("duration : %d\n", duration);
	printf("sentence: %s\n", sentence);

}

void tasksList(int ids[]) {

	int i;
	for (i=0; ids[i] != '\0'; i++) {
		printf("id : %d\n", ids[i]);
	}
}