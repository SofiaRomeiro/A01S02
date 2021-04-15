#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXTASKS 10000
#define USERNAME 20
#define MAXUSERS 50 
#define MAXACTIVS 10
#define DESCFORTASK 50
#define DESCFORACTIV 20

typedef struct user {
	char username[USERNAME+1];
} user_t;

typedef struct activity {
	char name[DESCFORACTIV+1];
} activity_t;

typedef struct task {
	int id;
	char description[DESCFORTASK+1];
	char username[USERNAME+1];
	char activity_name[DESCFORACTIV+1]; 
	int duration;
	int start_time;
} task_t;

int count_tasks = 0;
int count_users = 0;	
int count_activities = 3;
int time_now=0;
task_t tasks_list[MAXTASKS]; 
user_t users_list[MAXUSERS];
activity_t activities_list[MAXACTIVS];

int readT(char description[]);
int readL(int ids[]);
int readN();
int readU(char user[]);
int readM(char user[], char activity[]);
void readD(char activity[]);
int readA(char activity[]);

void newTask(int duration, char description[]);
void tasksList(int ids_lfunc_counter, int ids_lfunc[]);
void timeAdder(int duration);
void newUser(char user[], int user_exist);
void moveTask(int id, char newuser[], char newactivity[]);
void allTasksList(char newactivity[]);
void addActivity(char activity[], int activ_exist);

void exch(task_t sort[], int i, int j);
int lessL(char v[], char a_j[]);
int partitionL(task_t sort[], int l, int r);
void quicksortL(task_t sort[], int l, int r);
int lessN(int v, int a_j);
void insertion(task_t a[], int l, int r);

int main() {
	int quit = 0;
	int duration, id, ids_lfunc_counter, user_exist, activ_exist, ids_lfunc[MAXTASKS];
	char command, newdescription[DESCFORTASK + 1], newuser[USERNAME+1], newactivity[DESCFORACTIV+1];	
	strcpy(activities_list[0].name, "TO DO");
	strcpy(activities_list[1].name, "IN PROGRESS");
	strcpy(activities_list[2].name, "DONE");	
	while ( !quit ) {
		command = getchar();
		switch (command) {
			case 't':
				duration = readT(newdescription);			
				newTask(duration, newdescription); 
				break;
			case 'l':
				/* if the user doesn't introduce id's, readL returns 0, else returns the number of id's asked*/
				ids_lfunc_counter = readL(ids_lfunc);
				tasksList(ids_lfunc_counter, ids_lfunc);
				break;
			case 'n':
				/* returns -1 if failed => negative, decimal or not number */
				duration = readN();
				timeAdder(duration);
				break;
			case 'u':
				/* returns 1 if exists user, 0 if it doesn't */
				user_exist = readU(newuser);			
				newUser(newuser, user_exist);
				break;
			case 'm':
				id = readM(newuser, newactivity);
				moveTask(id, newuser, newactivity);
				break;
			case 'd':
				readD(newactivity);
				allTasksList(newactivity);
				break;
			case 'a':
				activ_exist = readA(newactivity);
				addActivity(newactivity, activ_exist);
				break;			
			case 'q':
				quit = 1;
				break;			
			default:
				break;
		}
	}
	return 0;
}

/******************************************************************
*																  *
*    					READ FUNCTIONS							  *
*																  *
**************************************************************** */

int readT(char newdescription[]) {
	/*
	* Function:  readT
	* --------------------
	* Reads the duration and the description from terminal to create a new task
	*
	* newdescription: new tasks' description 
	*
	* returns: duration or a negative number in case of an invalid duration         
	*           
	*/
	int i, duration=0, index=0, negative = 1, start_description=0, start_num=0, end_num=0;
	char c;	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {		
		/* espaco ou tabulador antes do numero */
		if ((c == ' ' || c == '\t') && !start_num && !start_description) {
			continue;
		} 
		/* numero negativo */
		else if (c == '-' && !start_num && !start_description) {
			negative = -1;
		}
		/* numero */
		else if (c>='0' && c <= '9' && !end_num) {
			start_num = 1;
			duration = duration * 10 + (c - '0');
		}
		else if ((c=='.' || c==',') && start_num && !start_description) {
			negative = -1;
		}
		/* espaco ou tabulador */
		else if ((c == ' ' || c == '\t') && start_num && !start_description) {
			end_num = 1;	
		}
		/* descricao */		
		else if (end_num && index <= DESCFORTASK) {
			newdescription[index++] = c;
			start_description = 1;
		}		
	}
	newdescription[index] = '\0';
	return duration*negative;
}

int readL(int ids_lfunc[]) {
	/*
	* Function:  readL
	* --------------------
	* Reads a list of id's asked to print the respective task
	*
	* ids_lfunc: list of id's introduced 
	*
	* returns: the amount of id's introduced or 0 if any id has been introduced         
	*           
	*/
	char c;
	int id=0, i, index=0, reading=0, exist_id=0, negative=1;	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {
		/* se c for numero, continua a ler e construir numero ate encontrar espaco */
		if (c>= '0' && c<= '9') {
			id = id * 10 + (c - '0');
			reading = 1;
			exist_id = 1;
		}
		else if (c=='-' && !reading) {
			negative = -1;
			reading = 1;
			exist_id=1;
		}
		/* se c for ' ' ou '\t' -> passa a frente, adiciona o id ao array e da clean no id*/
		else if (reading && (c == ' ' || c == '\t')) {
			ids_lfunc[index++] = id*negative;
			id = 0;	
			reading = 0;
			negative=1;
		}
		else if (!reading && (c == ' ' || c == '\t')){			
			continue;
		}			
	}
	ids_lfunc[index++] = id*negative;
	return  exist_id ? index : 0;
}

int readN() {
	/*
	* Function:  readN
	* --------------------
	* Reads the amount of time to add to the current time
	*
	* returns: time if the introduced value is a valid time or -1 if it's invalid        
	*           
	*/
	int time = 0, reading=0, end = 0, failed = 0, num_found=0;
	char c;
	while ((c = getchar()) != EOF && c != '\n') {
		/* comeca a ler o numero */
		if (c >= '0' && c <= '9' && !end && !failed) {
			time = time * 10 + (c - '0');
			reading = 1;
			num_found = 1;
		}
		/* ainda nao encontrou nenhum numero e nao esta a ler */
		else if ((c == ' ' || c == '\t') && !reading && !end && !failed){
			continue;
		}
		/* ja encontrou o numero e ja leu 1 numero */
		else if ((c == ' ' || c == '\t') && !failed) {
		/*	reading = 0;*/
			end = 1;
		}
		/* caracteres inseridos nao validos */
		else if (!failed){
			failed = 1;
		}
	}
	/* if doesn't read any time, reads a decimal or a negative number returns -1, else returns the time to add*/
	return (!failed && num_found) ? time : -1;
}

int readU(char newuser[]) {
	/*
	* Function:  readU
	* --------------------
	* Reads the username introduced to create a new user
	*
	* newuser: new user's username 
	*
	* returns: if a user has been introduced returns 1, else returns 0
	*           
	*/
	int i, u= 0, start_reading=0, end_reading=0, exist_user=0;
	char c;		
	for (i=0; ((c=getchar()) != EOF) && c != '\n'; i++) {
		if ((c == ' ' || c == '\t') && !start_reading) {
			continue;
		}
		else if (c != ' ' && !end_reading && u<=USERNAME) {
			newuser[u++] = c;
			start_reading = 1;
			exist_user=1;
		}
		else if ((c == ' ' || c == '\t') && start_reading) {
			end_reading = 1;
			continue;
		}
	}
	newuser[u] = '\0';
	return exist_user ? 1 : 0;
}

int readM(char newuser[], char newactivity[]) {
	/*
	* Function:  readM
	* --------------------
	* Reads the id of the task, which user the task is assigned to and the activity to be atributted 
	*
	* newuser: the user to whom the task is assigned
	* newactivity: the activity that will be assigned to the introduced id
	*
	* returns: introduced id or a negative number, in case of an invalid id being introduced        
	*           
	*/
	int id=0, u=0, a=0, reading=0, a_found=0, id_read=0, user_read=0, activity_read=0, negative=1;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {		
		/* espaco ou '\t' antes do numero */
		if ((c == ' ' || c == '\t') && !id_read && !user_read && !activity_read && !reading) {
			continue;
		}
		/* numero negativo */
		else if (c=='-' && !id_read && !user_read && !activity_read && !reading) {
			negative = -1;
		}
		/* encontrei numero */
		else if (c>='0' && c <= '9' && !id_read && !user_read && !activity_read) {
			reading = 1;
			id = id * 10 + (c - '0');
		}
		/* a ler numero e encontro espaco */
		else if ((c == ' ' || c == '\t') && reading && !id_read && !user_read && !activity_read) {
			reading = 0;
			id_read = 1;	
		}
		/* encontro user */
		else if (c != ' ' && id_read && !user_read && u <= USERNAME && !activity_read) {
			reading = 1;
			newuser[u++] = c;
		}
		/* a ler user e encontro espaco */
		else if ((c == ' ' || c == '\t') && id_read && !activity_read && !a_found) {
			reading = 0;
			user_read = 1;
		}
		/* encontro atividade */		
		else if (id_read && user_read && a <= DESCFORACTIV) {
			newactivity[a++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	newuser[u] = '\0';
	newactivity[a] = '\0';
	return id*negative;
}

void readD(char newactivity[]) {
	/*
	* Function:  readD
	* --------------------
	* Reads the requested activity  
	*
	* newactivity: the activity that will be requested       
	*           
	*/
	int a=0,a_found=0;
	char c;	
	while ((c=getchar()) != EOF && c != '\n') {	
		/* encontro espaco */
		if ((c == ' ' || c == '\t') && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a <= DESCFORACTIV) {
			newactivity[a++] = c;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';
}

int readA(char newactivity[]) {
	/*
	* Function:  readA
	* --------------------
	* Reads the name of the new activity that will be created
	*
	* newactivity: the new activity's name 
	*
	* returns: if there's an activity introduced        
	*           
	*/
	int a=0,a_found=0, exist_activity=0;
	char c;	
	while ((c=getchar()) != EOF && c != '\n') {	
		/* encontro espaco */
		if ((c == ' ' || c == '\t') && !a_found) {
			continue;
		}
		/* encontro atividade */		
		else if (a <= DESCFORACTIV) {
			newactivity[a++] = c;
			exist_activity=1;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';
    return exist_activity ? 1 : 0;
}

/******************************************************************
*																  *
*    					EXECUTE FUNCTIONS						  *
*																  *
**************************************************************** */

void newTask(int duration, char newdescription[]) {
	/*
	* Function:  newTask
	* --------------------
	* Creates a new task
	*
	* duration: new task's duration
	* newdescription : new task's description
	*
	* returns: if there's an activity introduced        
	*           
	*/
	int i, index;
	/* se a task for criada, adiciona 1 ao conta tasks, se com essa adição ficar maior que MAXTASKS, nao cria */
	if (count_tasks + 1 > MAXTASKS ) {
		printf("too many tasks\n");
		return;
	} 
	/* neste momento existem count_tasks criadas, logo percorre ate i < numero de tasks */
	for (i=0; i < count_tasks; i++) {
		if (!strcmp(tasks_list[i].description, newdescription)) {
			printf("duplicate description\n");
			return;
		}
	}
	if (duration <= 0) {
		printf("invalid duration\n");
		return;
	}
	count_tasks++;
	/* qualquer index é sempre count_tasks-1 */
	index = count_tasks-1;	
	tasks_list[index].id = count_tasks;
	strcpy(tasks_list[index].description, newdescription);
	strcpy(tasks_list[index].activity_name, "TO DO");
	tasks_list[index].duration = duration;
	tasks_list[index].start_time = 0;	
	/* saida : task <id> */	
	printf("task %d\n", tasks_list[index].id);
	return;
}

void tasksList(int ids_lfunc_counter, int ids_lfunc[]) {
	/*
	* Function:  tasksList
	* --------------------
	* If there are introduced ids, prints the task's id, activity nam, duration and description
	*
	* ids_lfunc_counter: number of id's introduced
	* ids_lfunc: array of introduced id's
	*                 
	*/
	int i, j, index;
	task_t sort[MAXTASKS];	
	if (ids_lfunc_counter==0) {	
	/* interessa me um array com id's das tarefas ordenados */
		for (i=0; i < count_tasks; i++) {
			sort[i] = tasks_list[i];
		}		
		quicksortL(sort, 0, count_tasks-1); /* existem n=count_tasks pelo que o vetor vai de 0 até n-1 tasks */
		for (i=0; i < count_tasks; i++) {
			printf("%d %s #%d %s\n",sort[i].id, sort[i].activity_name, sort[i].duration, sort[i].description);
		}
		return;
	}
	/* se houver ids inseridos */
	for (i=0; i < ids_lfunc_counter; i++) {
		if (!(ids_lfunc[i] <= count_tasks && ids_lfunc[i] > 0)) {
			printf("%d: no such task\n", ids_lfunc[i]);
		}
		else {
			for (j=0; j < count_tasks; j++) {			
				if (ids_lfunc[i] == tasks_list[j].id) {
					index=ids_lfunc[i]-1;
					printf("%d %s #%d %s\n",tasks_list[index].id, tasks_list[index].activity_name, tasks_list[index].duration, tasks_list[index].description);
				}
			}			
		}
	}	
	return;
}

void timeAdder(int duration) {
	if (duration < 0) {
		printf("invalid time\n");
		return;
	}
	time_now += duration;
	printf("%d\n", time_now);
	return;
}

void newUser(char newuser[], int user_exist) {
	int i=0, index;
	/* Errors */	
	for (i=0; (i < count_users) && user_exist; i++) {
		if (!(strcmp(newuser, users_list[i].username))) {
			printf("user already exists\n");
			return;
		}
	}
	/* se o user for criado,acrescenta 1 e se users+1 > MAXUSERS, nao pode ser criado */
	if ((count_users + 1 > MAXUSERS) && user_exist) {
		printf("too many users\n");
		return;
	}
	if (!user_exist) {
		for (i=0; i < count_users; i++) {
			printf("%s\n", users_list[i].username);
		}
		return;
	}
	/* itera o contador de users assim que sera possivel criar um user */
	count_users++;
	index = count_users-1;	
	strcpy(users_list[index].username, newuser);
	return;
}

void moveTask(int id, char newuser[], char newactivity[]) {	
    int i, valid_activity=0,valid_user=0, index;
	index = id-1; /* a posicao da task no array vai ser o id pedido menos 1, ou seja, id-1 */
    /* se o user tentar mover a tarefa para a atividade onde esta ja esta */
	if (!(strcmp(tasks_list[index].activity_name, newactivity))) {
		return;
	}
    if (!(id <= count_tasks && id>0)) {
        printf("no such task\n");
        return;
    }	
	/* se a task ja tiver saido de TO DO (sido iniciada) e a tentarem mover para TO DO */
	if (!(strcmp(newactivity, "TO DO")) && strcmp(tasks_list[index].activity_name, "TO DO")) {
		printf("task already started\n");
		return;
	}
    for (i=0; i < count_users; i++) {
        if (!strcmp(newuser, users_list[i].username)) {
			valid_user = 1;	
            break;	
        }
    }
	if (!valid_user) {
		printf("no such user\n");
		return;
	}
    for (i=0; i < count_activities; i++) {
        if (!(strcmp(newactivity, activities_list[i].name))) {
			valid_activity = 1; 
            break;       
        }
    }
	if (!valid_activity) {
		printf("no such activity\n");
    	return;
	}
	/* se a atividade estava no TO DO e vai sair, comeca a contar o tempo de inicio*/
	if (!(strcmp(tasks_list[index].activity_name, "TO DO"))) {
		tasks_list[index].start_time = time_now;	
	}
	strcpy(tasks_list[index].activity_name, newactivity);
	strcpy(tasks_list[index].username, newuser);
    if (!(strcmp(newactivity, "DONE"))) {
        printf("duration=%d slack=%d\n", (time_now - tasks_list[index].start_time), ((time_now - tasks_list[index].start_time) - tasks_list[index].duration));
    }
	return;
}

void allTasksList(char newactivity[]) {
	int i, valid_acivity=0;
	task_t sort_activitie_tasks[MAXTASKS];
	int n=0;
	for (i=0; i < count_activities; i++) {
		if (!(strcmp(newactivity, activities_list[i].name))) {
			valid_acivity = 1;
		}
	}
	if (!valid_acivity) {
		printf("no such activity\n");
		return;
	}
	for (i=0; i < count_tasks; i++) {
		if (!strcmp(newactivity, tasks_list[i].activity_name)) {
			sort_activitie_tasks[n] = tasks_list[i];	
			n++;
		}
	}	
	/* como n e iterado uma ultima vez e nao ha adicao ao vetor, na pratica existem n-1 posicoes no vetor */
	quicksortL(sort_activitie_tasks, 0, n-1); 
    insertion(sort_activitie_tasks, 0, n-1);
	for (i=0; i < n; i++) {
		printf("%d %d %s\n", sort_activitie_tasks[i].id, sort_activitie_tasks[i].start_time, sort_activitie_tasks[i].description);
	} 	
	return;
}

void addActivity(char newactivity[], int activ_exist) {
	int i, len = strlen(newactivity);
	int index;
    for(i=0; i < count_activities; i++) {
        if (!(strcmp(activities_list[i].name, newactivity))) {
            printf("duplicate activity\n");
            return;
        }
    }	
    for (i=0; i <= len; i++) {		
        if ((newactivity[i] >= 'a' && newactivity[i] <= 'z')) {
            printf("invalid description\n");
            return;
        }
    }
	/* a atividade so e iterada aquando da possivel criacao, logo se a tarefa for criada e passar as 10, nao pode ser criada */
	if (count_activities + 1 > MAXACTIVS) {
		printf("too many activities\n");
		return;
	}
	if (activ_exist) {
		count_activities++;
		/* a posicao do array de atividades é sempre a quantidade de atividades menos 1, ou seja, atividades-1 */
		index = count_activities - 1;	
		strcpy(activities_list[index].name, newactivity);
		return;
	}	
	for (i=0; i < count_activities; i++) {
		printf("%s\n", activities_list[i].name);
	}
	return;
}


/*  ************************************************************ 
    |					sort Phrases
    ************************************************************ */

void exch(task_t sort[], int i, int j) {
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
	char v[DESCFORTASK+1];
	strcpy(v,sort[r].description); 
	while (i < j) { 				
		while (lessL(sort[++i].description, v));				
		while (lessL(v, sort[--j].description)) 
			if (j == l) 
				break;
		if (i < j)
			exch(sort, i, j); 
	}
	exch(sort, r, i);
	return i; 
}

void quicksortL(task_t sort[], int l, int r) {
	int i;
	if (r <= l)
		return;
	i = partitionL(sort, l, r);
	quicksortL(sort, l, i-1);
	quicksortL(sort, i+1, r);
}

/* ************************************************************ 
						sort Numbers
   ************************************************************ */
int lessN(int v, int a_j) {
	if (v< a_j) {
		return 1;
	}	
	return 0;
}

void insertion(task_t a[], int l, int r) {
	int i,j;
	task_t v;
	for (i = l+1; i <= r; i++) {
		v = a[i];
		j = i-1;
		while ( j>=l && lessN(v.start_time, a[j].start_time)) {
			a[j+1] = a[j];
			j--;
		}
	a[j+1] = v;
	}
}