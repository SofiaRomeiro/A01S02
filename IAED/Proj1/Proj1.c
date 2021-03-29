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


void displaymenu();
int readnum();
void readsentence(char sentence[], int maxsize);
void newtask();

int main() {

	int quit = 0, duration = 0;
	char command;
	char description[DESCFORTASK + 1];
	
	while ( !quit ) {
		displaymenu();
		command = getchar();

		switch (command) {
			case 't':
				/* New Task */
				/* IN : t <duration> <description> */
				getchar();

				duration = readnum();
				readsentence(description, DESCFORTASK);

				newtask(duration, description);

				break;

			case 'l':
				/* tasks list
				taskslist(); */
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

void displaymenu() {
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

int readnum() {
	int num = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n' && c != ' ') {
		if (c >= '0' && c <= '9') {
			num = num * 10 + (c - '0');
		}
		else {
			printf("Please insert a positive number\n");
			exit(EXIT_FAILURE);
		}
	}
	return num;
}

void readsentence(char sentence[], int maxsize) {
	int i;
	char c;	
	for(i=0; i < (maxsize) && (c=getchar()) != EOF && c != '\n'; i++) {
		sentence[i] = c;
	}
	sentence[i] = '\0';
}

void newtask(int duration, char sentence[]) {

	printf("duration : %d\n", duration);
	printf("sentence: %s\n", sentence);

}