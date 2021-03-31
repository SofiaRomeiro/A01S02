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
				timeAdder(); */
				getchar();
				duration = readNum();
				timeAdder(duration);
				break;

			case 'u':
				/* add new user or new list of users 
				newuser(); */
				getchar();
				readUser(user, USERNAME);
				newUser(user);
				break;

			case 'm':
				/* move task from one activitie to another
				movetask(); */
				getchar();
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


struct task {
	int id;
	char description[DESCFORTASK+1];
	char user[USERNAME];
	char activitie[DESCFORACTIV];
	int duration;
	int start_time;
}; 

struct activitie {
	char description[DESCFORACTIV];
	char tasks[];
};

struct user {
	char user[USERNAME];
	int users;
};

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
			sentence[n] = temporary[j];
			n++;
			reading = 1;
		}
	}
	sentence[n] = '\0';
}

void readUser(char user[], int maxsize) {
	int i, j = 0;
	int char_found = 0;
	char c;	
	
	for(i=0; i < (maxsize) && (c=getchar()) != EOF && c != '\n'; i++) {
		if 	(c == ' ' && !char_found) {
			continue;
		}	
		else if (c != ' ') {
			user[j] = c;
			j++;
			char_found = 1;
		}
		else if (c == ' ' && char_found) {
			user[j] = '\0';	
			char_found = 0;			
			break;
		}
		else {
			user[j]='\0';
			break;
		}
	}
	user[j] = '\0';		
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