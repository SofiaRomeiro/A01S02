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

/* Global vars */
int count_tasks = 0;
int count_users = 0;
/* 3 pre created activities -> start counting = 3 */
int count_activities = 3;
int time_now=0;

task_t tasks_list[MAXTASKS]; 
user_t users_list[MAXUSERS];
activity_t activities_list[MAXACTIVS];


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
int newTask(int duration, char description[]);
int tasksList(int ids_lfunc_counter, int ids_lfunc[]);
void timeAdder(int duration);
int newUser(char user[], int user_exist);
int moveTask(int id, char newuser[], char newactivity[]);
int allTasksList(char newactivity[]);
int addActivity(char activity[], int activ_exist);

/* Auxiliar functions */
void exchL(task_t sort[], int i, int j);
int lessL(char v[], char a_j[]);
int partitionL(task_t sort[], int l, int r);
void quicksortL(task_t sort[], int l, int r);

void exchN(task_t sort[], int i, int j);
int lessN(task_t sort[], int v, int a_j, int x, int y);
int partitionN(task_t sort[], int l, int r);
void quicksortN(task_t sort[], int l, int r);


int main() {
	/* '+1' means the maximum size plus '\0' */
	int quit = 0;
	int duration = 0, id=0, ids_lfunc_counter=0;
	int user_exist=0, activ_exist=0;
	char command;	
	int ids_lfunc[MAXTASKS];

	char newdescription[DESCFORTASK + 1];
	char newuser[USERNAME+1];
	char newactivity[DESCFORACTIV+1];
	
	strcpy(activities_list[0].name, "TO DO");
	strcpy(activities_list[1].name, "IN PROGRESS");
	strcpy(activities_list[2].name, "DONE");

	
	while ( !quit ) {
	/*	displayMenu(); */
		command = getchar();

		switch (command) {
			case 't':
				/* t <duration> <description> */
				duration = readT(newdescription);
				/* for each task created, adds 1 more to count_tasks */
			/*	count_tasks++; */
				newTask(duration, newdescription); 
				break;

			case 'l':
				/* l [<id> <id> ...] */
				ids_lfunc_counter = readL(ids_lfunc);
				/* if the user doesn't introduce id's, readL returns 0, else returns the number of id's asked*/
				tasksList(ids_lfunc_counter, ids_lfunc);
				break;

			case 'n':
				/*  n <duração> */
				duration = readN();
				if (duration >= 0) { 
					timeAdder(duration);
				}
				break;

			case 'u':
				/*  u [<utilizador>] */
				/* devolve 1 se existir user, 0 se nao existir */
				user_exist = readU(newuser);
			/*	if (user_exist) {
                    count_users++;
                } */
				newUser(newuser, user_exist);
				break;

			case 'm':
				/* m <id> <utilizador> <atividade> */
				id = readM(newuser, newactivity);
				moveTask(id, newuser, newactivity);
				break;

			case 'd':
				/* d <atividade> */
				readD(newactivity);
				allTasksList(newactivity);
				break;

			case 'a':
				/* a [<atividade>]*/
				activ_exist = readA(newactivity);
				if (activ_exist) {
                    count_activities++;
                }
				addActivity(newactivity, activ_exist);
				break;
			
			case 'q':
				quit = 1;
				break;
			
			default:
				printf("Error : Command Not Found\n");
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

int readL(int ids_lfunc[]) {
	char c;
	int id=0, i, index=0, reading=0, exist_id=0;
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
			ids_lfunc[index++] = id;
			id = 0;	
			reading = 0;
		}

		else if (!reading && c == ' '){			
			continue;
		}			
	}
	if (id > 0) {
		ids_lfunc[index++] = id;
	}
	
	return  exist_id ? index : 0;
}

int readN() {
	int time = 0, reading = 0, end = 0, failed = 0;
	char c;

	while ((c = getchar()) != EOF && c != '\n') {

		/* comeca a ler o numero */
		if (c >= '0' && c <= '9' && !end && !failed) {
			time = time * 10 + (c - '0');
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
		else if (!failed){
			printf("invalid time\n");
			failed = 1;
		}
	}
	/* if doesn't read any time, returns -1, else returns the time to add*/
	return !failed ? time : -1;
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

	int id=0, u=0, a=0, reading=0, a_found=0;	
	int id_read=0;
	int user_read=0;
	int activity_read=0;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {		
		/* espaco antes do numero */
		if (c == ' ' && !id_read && !user_read && !activity_read && !reading) {
			continue;
		}
		/* encontrei numero */
		else if (c>='0' && c <= '9' && !id_read && !user_read && !activity_read) {
			reading = 1;
			id = id * 10 + (c - '0');
		}
		/* a ler numero e encontro espaco */
		else if (c == ' ' && reading && !id_read && !user_read && !activity_read) {
			reading = 0;
			id_read = 1;	
		}
		/* encontro user */
		else if (c != ' ' && id_read && !user_read && u < USERNAME && !activity_read) {
			reading = 1;
			newuser[u++] = c;
		}
		/* a ler user e encontro espaco */
		else if (c == ' ' && id_read && !activity_read && !a_found) {
			reading = 0;
			user_read = 1;
		}
		/* encontro atividade */		
		else if (id_read && user_read && a < DESCFORACTIV) {
			newactivity[a++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	newuser[u] = '\0';
	newactivity[a] = '\0';

	return id;
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

	int a=0,a_found=0, exist_activity=0;
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

int newTask(int duration, char description[]) {

	int i;

	if (count_tasks == MAXTASKS + 1) {
		printf("too many tasks\n");
		return 0;
	} 

	for (i=0; i < count_tasks-1; i++) {s
		if (strcmp(tasks_list[i].description, description) == 0) {
			printf("duplicate description\n");
			return 0;
		}
	}

	tasks_list[count_tasks-1].id = count_tasks;

	for (i=0; description[i] != '\0'; i++) {
		tasks_list[count_tasks-1].description[i] = description[i];
	}
	tasks_list[count_tasks-1].description[i] = '\0';

	strcpy(tasks_list[count_tasks-1].activity_name, "TO DO");

	tasks_list[count_tasks-1].duration = duration;
	tasks_list[count_tasks-1].start_time = 0;
	
	/* saida : task <id> */	
	printf("task %d\n", tasks_list[count_tasks-1].id);

	return 0;
}

int tasksList(int ids_lfunc_counter, int ids_lfunc[]) {
	int i, j;
	task_t sort[MAXTASKS];

	if (ids_lfunc_counter==0) {
	
	/* interessa me um array com id's das tarefas ordenados */

		for (i=0; i < count_tasks; i++) {
			sort[i] = tasks_list[i];
		}			

		quicksortL(sort, 0, count_tasks-1);

		for (i=0; i < count_tasks; i++) {
			printf("%d %s #%d %s\n",sort[i].id, sort[i].activity_name, sort[i].duration, sort[i].description);
		}
	
	}

	/* ------------------------------------------------------ */
	/* se houver ids inseridos */

	/*ids_lfunc_counter, ids_lfunc*/	

	for (i=0; i < ids_lfunc_counter; i++) {
		for (j=0; j < count_tasks; j++) {
			if (ids_lfunc[i] > count_tasks){
				printf("%d: no such task\n", ids_lfunc[i]);
				return 0;
			}	
		}
	}	

	for (i=0; i < ids_lfunc_counter; i++) {
		for (j=0; j < count_tasks; j++) {
			if (ids_lfunc[i] == tasks_list[j].id) {
				printf("%d %s #%d %s\n",tasks_list[i].id, tasks_list[j].activity_name, tasks_list[j].duration, tasks_list[j].description);
			}
			
		}
	}	
	return 0;
}

void timeAdder(int duration) {

	if (duration == 0) {
		printf("%d\n", time_now);
	}
	else {
		time_now += duration;
		printf("%d\n", time_now);
	}
}

int newUser(char newuser[], int user_exist) {

	int i=0;

	/* Errors */
	
	for (i=0; i < (count_users) && user_exist; i++) {
		if (!(strcmp(newuser, users_list[i].username))) {
			printf("user already exists\n");
			return 0;
		}
	}

	if (count_users == MAXUSERS && user_exist) {
		printf("too many users\n");
		return 0;
	}
	

	if (!user_exist) {
		for (i=0; i < count_users; i++) {
			printf("%s\n", users_list[i].username);
		}
	}

	count_users++;
	
	strcpy(users_list[count_users-1].username, newuser);
	return 0;
	


/*	printf("number of users : %d\n", count_users);

	printf("user 0 : %s\n", users_list[0].username);

	for (i=0; i < count_users; i++) {
		printf("user : %s\n", users_list[i].username);
	} */




	return 0;
}

int moveTask(int id, char newuser[], char newactivity[]) {	

    int i, valid_activitie=0;	

	printf("id : %d, count: %d\n", id, count_tasks);

    if (id > count_tasks) {
        printf("no such task\n");
        return 0;
    }
	
	if (!(strcmp(newactivity, "TO DO"))) {
		printf("task already started\n");
		return 0;
	}

    for (i=0; i < count_users; i++) {
        if (strcmp(newuser, users_list[i].username)) {
            printf("no such user\n");
            return 0;
        }
    }

    for (i=0; i < count_activities; i++) {
        if (!(strcmp(newactivity, activities_list[i].name))) {
			valid_activitie = 1;        
        }
    }
	if (!valid_activitie) {
		printf("no such activitie\n");
    	return 0;
	}

	if ((strcmp(newactivity, "TO DO"))) {
		if (!(strcmp(tasks_list[id-1].activity_name, "TO DO"))) {
			tasks_list[id-1].start_time = time_now;	
		}
		strcpy(tasks_list[id-1].activity_name, newactivity);
		strcpy(tasks_list[id-1].username, newuser);
	}	

    if (!(strcmp(newactivity, "DONE"))) {
        printf("duration=%d slack=%d\n", (time_now - tasks_list[id-1].start_time), ((time_now - tasks_list[id-1].start_time) - tasks_list[id-1].duration));
    }

	return 0;
}

int allTasksList(char newactivity[]) {
	int i, valid_acivity=0;
	task_t sort_activitie_tasks[MAXTASKS];
	int tasks_asked=0;
	int n=0;

	for (i=0; i < count_activities; i++) {
		if (!(strcmp(newactivity, activities_list[i].name))) {
			valid_acivity = 1;
		}
	}

	if (!valid_acivity) {
		printf("no such activity\n");
		return 0;
	}


	for (i=0; i < count_tasks; i++) {
		if (!strcmp(newactivity, tasks_list[i].activity_name)) {
			sort_activitie_tasks[n++] = tasks_list[i];			
			tasks_asked++;
		}
	}	

	quicksortN(sort_activitie_tasks, 0, tasks_asked-1);	

	for (i=0; i < tasks_asked; i++) {
		printf("%d %d %s\n", sort_activitie_tasks[i].id, sort_activitie_tasks[i].start_time, sort_activitie_tasks[i].description);
	} 
	
	return 0;
}

int addActivity(char newactivity[], int activ_exist) {

	int i, len = strlen(newactivity);

    for(i=0; i < count_activities; i++) {
        if (!(strcmp(activities_list[i].name, newactivity))) {
            printf("duplicate activity\n");
            return 0;
        }
    }

	
    for (i=0; i < len; i++) {		
        if ((newactivity[i] >= 'a' && newactivity[i] <= 'z')) {
            printf("invalid description\n");
            return 0;
        }
    }

	if (count_activities >= 10) {
		printf("too many activities\n");
		return 0;
	}

	if (activ_exist) {
		strcpy(activities_list[count_activities-1].name, newactivity);
	}

	else {
		for (i=0; i < count_activities; i++) {
			printf("%s\n", activities_list[i].name);
		}
	}

	return 0;
}


/* ************************************************************ 
						sort D
   ************************************************************ */
void exchN(task_t sort[], int i, int j) {
	task_t temp;
	temp = sort[i];
	sort[i] = sort[j];
	sort[j] = temp;
}


int lessN(task_t sort[], int v, int a_j, int x, int y) {

	int res;

	if (v < a_j) {
		return 1;
	}	
	else if( v == a_j) {
		res = strcmp(sort[x].description, sort[y].description);
		if (res < 0) {
			return 1;
		}
	}
	return 0;
}


int partitionN(task_t sort[], int l, int r) {

	int i = l+1; 
	int j = r; 
	int v = sort[r].start_time; /* pivo */
	while (i < j) { /* enquanto o iterador da esquerda for menor do que o da direita */	
		while (lessN(sort, sort[i].start_time, v, i, r)) ++i; /* procura elemento maior que o pivot -> */		
		while (lessN(sort, v, sort[j].start_time, r, j)) /* procura elemento menor que o pivot <- */
			if (j == l) /* para quando o elemento da particao esta na primeira posicao */
				break;
		--j;
		if (i < j)
			exchN(sort, i, j); /* troca se o maior para a posicao do menor e vice versa */
	}
	exchN(sort, r, i); /* no fim de tudo, troca o pivo (a[r]) com o numero do meio (a[j])  */

	return i; /* retorna o ponto onde partiu o vetor, ou seja, o meio */
}

void quicksortN(task_t sort[], int l, int r) {
	int i;

	if (r <= l)
		return;

	i = partitionN(sort, l, r);

	quicksortN(sort, l, i-1);
	quicksortN(sort, i+1, r);
	
}




/* ************************************************************ 
						sort L
   ************************************************************ */

void exchL(task_t sort[], int i, int j) {
	task_t temp;

	temp = sort[i];
	sort[i] = sort[j];
	sort[j] = temp;

}

int lessL(char v[], char a_j[]) {

	if (strcmp(v,a_j)<0) {
		return 1;
	}

	return 0;
}

int partitionL(task_t sort[], int l, int r) {
	int i = l-1; 
	int j = r; 
	char v[DESCFORTASK];
	strcpy(v,sort[r].description); /* pivo -> primeira letra da ultima frase */
	while (i < j) { /* enquanto o iterador da esquerda for menor do que o da direita */				
		while (lessL(sort[++i].description, v)); /* procura elemento maior que o pivot -> */				
		while (lessL(v, sort[--j].description)) /* procura elemento menor que o pivot <- */ 
			if (j == l) /* para quando o elemento da particao esta na primeira posicao */
				break;
		if (i < j)
			exchL(sort, i, j); /* troca se o maior para a posicao do menor e vice versa */
	}
	exchL(sort, r, i); /* no fim de tudo, troca o pivo (a[r]) com o numero do meio (a[j])  */
	return i; /* retorna o ponto onde partiu o vetor, ou seja, o meio */
}

void quicksortL(task_t sort[], int l, int r) {

	int i;
	if (r <= l)
		return;

	i = partitionL(sort, l, r);
	quicksortL(sort, l, i-1);
	quicksortL(sort, i+1, r);
}

