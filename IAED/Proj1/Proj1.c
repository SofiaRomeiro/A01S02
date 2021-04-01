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
int readT(char description[]);
void readSentence(char sentence[], int maxsize);
void readListId(int list[], int maxsize);
void newTask();
void tasksList(int ids[]);
void timeAdder(int duration);
void readUser(char user[], int maxsize);
void newUser(char user[]);
void moveTask(int id, char user[], char activitie[]);
void allTasksList(char activities[]);
void addActivitie(char activities[]);

int main() {
	/* '+1' means the maximum size plus '\0' */
	int quit = 0, duration = 0, id=0;
	char command;
	char description[DESCFORTASK + 1];
	int ids[IDENTIFIER+2];
	char user[USERNAME+1];
	char activitie[DESCFORACTIV+1];
	
	while ( !quit ) {
		displayMenu();
		command = getchar();

		switch (command) {
			case 't':
				duration = readT(description);
				newTask(duration, description);
				break;

			case 'l':
				/* tasks list
				taskslist(); */
				getchar();
				readListId(ids, IDENTIFIER);
				tasksList(ids);
				break;

			case 'n':
				/* time adder 
				timeAdder(); */
				getchar();
				duration = readNum();
				timeAdder(duration);
				break;

			case 'u':
				/* add new user or new list of users 
				newuser(); */
				readUser(user, USERNAME);
				newUser(user);
				break;

			case 'm':
				/* move task from one activitie to another
				movetask(); */
				id = readNum();
				readUser(user, USERNAME);
				readSentence(activitie, DESCFORACTIV);
				moveTask(id, user, activitie);
				break;

			case 'd':
				/* lists all tasks in one activitie 
				alltaskslist(); */
				getchar();
				readSentence(activitie, DESCFORACTIV);
				allTasksList(activitie);
				break;

			case 'a':
				/* add new activitie or list all activities 
				addActivitie(); */
				getchar();
				readSentence(activitie, DESCFORACTIV);
				addActivitie(activitie);
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

/* Command Functions */

int readT(char description[]) {
	/* t <duration> <description> */

	int i, num=0, index=0;
	int start_description=0;
	int start_num=0, end_num=0;
	char c;
	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {		
		/* espaco antes do numero */
		if (c == ' ' && !start_num && !start_description) {
			continue;
		}
		/* numero */
		else if (c>='0' && c <= '9' && !end_num) {
			start_num = 1;
			num = num * 10 + (c - '0');
		}
		/* espaco */
		else if (c == ' ' && start_num && !start_description) {
			end_num = 1;	
		}
		/* descricao */		
		else if (end_num && index < DESCFORTASK) {
			description[index++] = c;
			start_description = 1;
		}		
	}
	description[index] = '\0';

	return num;
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
	int i, j,n = 0;
	int reading=0;
	char temporary[DESCFORTASK];
	char c;	
	
	for(i=0; i < (maxsize) && (c=getchar()) != EOF && c != '\n'; i++) {
		temporary[i] = c;		
	}

	for (j=0; j < i; j++){
		if (temporary[j] == ' ' && !reading) {
			continue;
		}
		else {
			sentence[n++] = temporary[j];
			reading = 1;
		}
	}
	sentence[n] = '\0';

}


void readUser(char user[], int maxsize) {
	int i, u= 0;
	int start_reading=0, end_reading=0;
	char c;	
	
	for (i=0; i < maxsize && ((c=getchar()) != EOF) && c != '\n'; i++) {
		if (c==' ' && !start_reading) {
			continue;
		}
		else if (c != ' ' && !end_reading) {
			user[u++] = c;
			start_reading = 1;
		}
		else if (c == ' ' && start_reading) {
			end_reading = 1;
			continue;
		}
	}	
	user[u] = '\0';
}

void readListId(int list[], int maxsize) {
	char c;
	int id=0, i, idpos=0, reading=0;
	
	for (i=0; i < maxsize && (c=getchar()) != EOF && c != '\n'; i++) {
		/* se c for ' ' -> passa a frente, adiciona o id ao array e da clean no id*/
		if (c>= '0' && c<= '9') {
			id = id * 10 + (c - '0');
			reading = 1;
		}

		else if ((reading==1) && c == ' ') {
			list[idpos++] = id;
			id = 0;	
			reading = 0;
		}
		else if ((reading==0) && c == ' '){
			reading = 0;			
			continue;
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

void timeAdder(int duration) {
	printf("duration : %d\n", duration);
}

void newUser(char user[]) {
	printf("username : %s\n", user);
}

void moveTask(int id, char user[], char activitie[]) {
	printf("id :%d\nuser: %s\nactivitie: %s\n", id, user, activitie);
}

void allTasksList(char activitie[]) {
	printf("activitie : %s", activitie);
}

void addActivitie(char activitie[]) {
	printf("activitie : %s", activitie);
}