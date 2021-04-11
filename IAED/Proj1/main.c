#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* max number of tasks (id's max number [1, 10000]) = 10000 */
#define MAXTASKS 10000
/* max user len =  */
#define USERNAME 20
/* max users supported */
#define MAXUSERS 50 
/* max activities supported */
#define MAXACTIVS 10
/* max tasks' description len = 50 */
#define DESCFORTASK 50
/* max activities' description len = 20 */
#define DESCFORACTIV 20

/* Data Structures */
typedef struct user {
	char username[USERNAME+1];
} user_t;

typedef struct activity {
	char name[DESCFORACTIV+1]; 
	int len;
} activity_t;

typedef struct task {
	int id;
	char description[DESCFORTASK+1];
	char username[USERNAME+1];
	char activity_name[DESCFORACTIV+1]; 
	int duration;
	int start_time;
} task_t;

/* general functions */
void displayMenu();

/* command reader functions */
int readT(char description[]);
int readL(int ids[]);
int readN();
int readU(char user[]);
int readM(char user[], char activity[]);
void readD(char activity[]);
int readA(char activity[]);

/* Execute functions */
int newTask(int duration, char description[], int id_num, task_t tasks_list[]);
int tasksList(int ids[], int id_counter, task_t tasks_list[], int tasks_counter);
int timeAdder(int duration, int time_now);
int newUser(char user[], int user_exist, user_t users_list[], int users_num);
int moveTask(int id, char user[], char activity[], task_t tasks_list[]);
void allTasksList(char activities[]);
int addActivity(char activity[], int activ_exist, int activs_num, activity_t activities_list[]);

/* Global vars */
int count_tasks = 0;
int count_users = 0;
int count_activities = 0;

task_t tasks_list[MAXTASKS]; 
user_t users_list[MAXUSERS];
activity_t activities_list[MAXACTIVS];



int main() {
	/* '+1' means the maximum size plus '\0' */
	int quit = 0, duration = 0, id=0, id_counter=0, user_exist=0, activ_exist=0, id_num=0, users_num=0, activs_num=3, time_now=0;
	char command;
	char newdescription[DESCFORTASK + 1];
	int ids[MAXTASKS];
	char newuser[USERNAME+1];
	char newactivity[DESCFORACTIV+1];
	


	strcpy(activities_list[0].name, "TO DO");
	strcpy(activities_list[1].name, "IN PROGRESS");
	strcpy(activities_list[2].name, "DONE");

	while ( !quit ) {
		displayMenu();
		command = getchar();

		switch (command) {
			case 't':
				/* t <duration> <description> */
				duration = readT(newdescription);
				id_num++;
				newTask(duration, newdescription, id_num, tasks_list); 
				break;

			case 'l':
				/* l [<id> <id> ...] */
				id_counter = readL(ids);
				tasksList(ids, id_counter, tasks_list, id_num);
				break;

			case 'n':
				/*  n <duração> */
				duration = readN();
				if (duration >= 0) { 
					time_now = timeAdder(duration, time_now);
				}
				break;

			case 'u':
				/*  u [<utilizador>] */
				/* devolve 1 se existir user, 0 se nao existir */
				user_exist = readU(newuser);
				users_num++ ? user_exist : users_num;
				newUser(newuser, user_exist, users_list, users_num);
				break;

			case 'm':
				/* m <id> <utilizador> <atividade> */
				id = readM(newuser, newactivity);
				moveTask(id, newuser, newactivity, tasks_list);
				break;

			case 'd':
				/* d <atividade> */
				readD(newactivity);
				allTasksList(newactivity);
				break;

			case 'a':
				/* a [<atividade>]*/
				activ_exist = readA(newactivity);
				activs_num++ ? activ_exist : activs_num;
				addActivity(newactivity, activ_exist, activs_num, activities_list);
				break;
			
			case 'q':
				quit = 1;
				break;
			
			default:
				printf("Error : Command Not Found");
				break;
		}
	}
	return 0;
}

/*
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
} */

/* Command Read Functions */

int readT(char newdescription[]) {
	/* t <duration> <description> */

	int i, duration=0, index=0;
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
			duration = duration * 10 + (c - '0');
		}
		/* espaco */
		else if (c == ' ' && start_num && !start_description) {
			end_num = 1;	
		}
		/* descricao */		
		else if (end_num && index < DESCFORTASK) {
			newdescription[index++] = c;
			start_description = 1;
		}		
	}
	newdescription[index] = '\0';

	return duration;
}

int readL(int ids[]) {
	char c;
	int id=0, i, idpos=0, reading=0, exist_id=0;
	/* conta espacos para ver se se inseriu ids */
	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {

		/* se c for numero, continua a ler e construir numero ate encontrar espaco */
		if (c>= '0' && c<= '9') {
			id = id * 10 + (c - '0');
			reading = 1;
			exist_id = 1;
		}

		/* se c for ' ' -> passa a frente, adiciona o id ao array e da clean no id*/
		else if (reading && c == ' ') {
			ids[idpos++] = id;
			id = 0;	
			reading = 0;
		}

		else if (!reading && c == ' '){			
			continue;
		}			
	}
	if (id > 0) {
		ids[idpos++] = id;
	}
		

/*	for (i=0; i < idpos; i++){
		printf("id : %d\n", ids[i]);
	} */

	return  exist_id ? idpos : 0;
}

int readN() {
	int num = 0, reading = 0, end = 0, failed = 0;
	char c;
	while ((c = getchar()) != EOF && c != '\n') {

		/* comeca a ler o numero */
		 if (c >= '0' && c <= '9' && !end && !failed) {
			num = num * 10 + (c - '0');
			reading = 1;
		}

		/* ainda nao encontrou nenhum numero e nao esta a ler */
		else if (c == ' ' && !reading && !end && !failed){
			continue;
		}

		/* ja encontrou o numero e ja leu 1 numero */
		else if (c == ' ' && !failed) {
			reading = 0;
			end = 1;
		}

		/* caracteres inseridos nao validos */
		else {
			printf("invalid time\n");
			failed = 1;
		}
	}
	return !failed ? num : -1;
}

int readU(char newuser[]) {
	int i, u= 0;
	int start_reading=0, end_reading=0, exist_user=0;
	char c;	
	
	for (i=0; i < USERNAME && ((c=getchar()) != EOF) && c != '\n'; i++) {
		if (c==' ' && !start_reading) {
			continue;
		}
		else if (c != ' ' && !end_reading) {
			newuser[u++] = c;
			start_reading = 1;
			exist_user=1;
		}
		else if (c == ' ' && start_reading) {
			end_reading = 1;
			continue;
		}
	}	
	newuser[u] = '\0';
	return exist_user ? 1 : 0;
}

int readM(char newuser[], char newactivity[]) {
	/* m <id> <user> <activity> */

	int num=0, u=0, a=0, reading=0, a_found=0;	
	int num_read=0;
	int user_read=0;
	int activity_read=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {		
		/* espaco antes do numero */
		if (c == ' ' && !num_read && !user_read && !activity_read && !reading) {
			continue;
		}
		/* encontrei numero */
		else if (c>='0' && c <= '9' && !num_read && !user_read && !activity_read) {
			reading = 1;
			num = num * 10 + (c - '0');
		}
		/* a ler numero e encontro espaco */
		else if (c == ' ' && reading && !num_read && !user_read && !activity_read) {
			reading = 0;
			num_read = 1;	
		}
		/* encontro user */
		else if (c != ' ' && num_read && !user_read && u < USERNAME && !activity_read) {
			reading = 1;
			newuser[u++] = c;
		}
		/* a ler user e encontro espaco */
		else if (c == ' ' && num_read && !activity_read && !a_found) {
			reading = 0;
			user_read = 1;
		}
		/* encontro atividade */		
		else if (num_read && user_read && a < DESCFORACTIV) {
			newactivity[a++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	newuser[u] = '\0';
	newactivity[a] = '\0';

	return num;
}

void readD(char newactivity[]) {

	int a=0,a_found=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			newactivity[a++] = c;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';
}

int readA(char newactivity[]) {

	int a=0,a_found=0, exist_activity=0, i;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	

		/* encontro espaco */
		if (c == ' ' && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a < DESCFORACTIV) {
			newactivity[a++] = c;
			exist_activity=1;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';


	return exist_activity ? 1 : 0;
}

/* execute-type functions */

int newTask(int duration, char description[], int id_num, task_t tasks_list[]) {

	int i;

	if (id_num == MAXTASKS + 1) {
		printf("too many tasks\n");
		return 0;
	} 

	for (i=0; i < id_num-1; i++) {
		if (strcmp(tasks_list[i].description, description) == 0) {
			printf("duplicate description\n");
			return 0;
		}
	}

	tasks_list[id_num-1].id = id_num;

	for (i=0; description[i] != '\0'; i++) {
		tasks_list[id_num-1].description[i] = description[i];
	}
	tasks_list[id_num-1].description[i] = '\0';

	strcpy(tasks_list[id_num-1].activity_name, "TO DO");

	tasks_list[id_num-1].duration = duration;
	tasks_list[id_num-1].start_time = 0;
	
	/* saida : task <id> */	
	printf("task %d\n", tasks_list[id_num-1].id);

	return 0;
}

int tasksList(int ids[], int id_counter, task_t tasks_list[], int tasks_counter) {
	int i, j=1, num;

	if (id_counter==0) {
		/* imprimir por ordem alfabetica */
	}
	else {
		for (i=0; i < tasks_counter; i++) {
			for (j=0; j < id_counter; j++) {
				if (ids[i] == tasks_list[j].id) {
					printf("%d %s #%d %s\n",tasks_list[i].id, tasks_list[j].activity_name, tasks_list[j].duration, tasks_list[j].description);
				}
				else if (ids[i] > tasks_counter){
					printf("%d: no such task", ids[i]);
					return 0;
				}
			}
		}
	}

/*	for (i=0; i < id_counter; i++) {
		printf("id : %d\n", ids[i]);
	}
	printf("number of id's : %d\n", id_counter); */
	return 0;
}

int timeAdder(int duration, int time_now) {
	/*printf("duration : %d\n", duration);*/

	if (duration == 0) {
		printf("%d\n", time_now);
	}
	else {
		time_now += duration;
		printf("%d\n", time_now);
	}


	return time_now;

}

int newUser(char newuser[], int user_exist, user_t users_list[], int users_num) {

	int i=0;

	/* Errors */
	for (i=0; i < (users_num-1); i++) {
		if ((strcmp(newuser, users_list[i].username))==0) {
			printf("user already exists\n");
			return 0;
		}
	}

	if (users_num == MAXUSERS) {
		printf("too many users\n");
		return 0;
	}

	if (!user_exist) {
		for (i=0; i < users_num-1; i++) {
			printf("%s\n", users_list[i].username);
		}
	}
	else {
		for (i=0; newuser[i] != '\0'; i++) {
			users_list[users_num-1].username[i] = newuser[i];	
		}
		users_list[users_num-1].username[i] = '\0';
	/*	printf("created user number %d with username '%s'", users_num, users_list[users_num-1].username); */
	}

	return 0;
}

int moveTask(int id, char newuser[], char newactivity[], task_t tasks_list[]) {
	/*printf("id :%d\nuser: %s\nactivity: %s\n", id, newuser, newactivity); */

	strcpy(tasks_list[id-1].username, newuser);
	if (strcmp(newactivity, "TO DO") && !(strcmp(tasks_list[id-1].activity_name, "TO DO"))) {
		printf("task already started");
		return 0;
	}

	return 0;
}

void allTasksList(char newactivity[]) {	
	/*printf("activity : %s", newactivity); */
	int i, c=count_activities;

	for (i=0; i < count_activities; i++) {
		if (strcmp(newactivity, activities_list[]))
	}
}

int addActivity(char newactivity[], int activ_exist, int activs_num, activity_t activities_list[]) {

	int i;

/*	for (i=0; i < activs_num-1; i++) {
		if (strcmp(activities_list[i].name, newactivity) == 0) {
			printf("duplicate activity\n");
			return 0;
		}
	}

	for (i=0; i < a; i++) {
		if (newactivity[i] >= 'a' && newactivity[i] <= 'z') {
			printf("invalid description\n");
			return 0;
		}
	} */


	if (activs_num >= 10) {
		printf("too many activities\n");
		return 0;
	}

/*	printf("activs num = %d\n", activs_num);
	printf("activity : %s\n", newactivity);
	printf("%s\n", activ_exist ? "activity exist" : "activity does not exist"); */

	if (activ_exist) {
		for (i=0; newactivity[i] != '\0'; i++) {
			activities_list[activs_num-1].name[i] = newactivity[i];
		}
		activities_list[activs_num-1].name[i] = '\0';
	}
	printf("activitie : %s\n", activities_list[activs_num-1].name);
	return 0;
}

