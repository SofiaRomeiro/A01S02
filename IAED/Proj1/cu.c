/*-------------------------------------------*
|	IST 2020/2021 - IAED					 |
|											 |
|	1st Project : KANBAN BOARD in C language |
|											 |
|	Made by : Sofia Romeiro, ist198968		 |
|											 |
*-------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Limit number of tasks supported by the system */
#define MAXTASKS 10000 
/* Limit number of user supported by the system  */
#define MAXUSERS 50 
/* Limit number of activities supported by the system */
#define MAXACTIVS 10 
/* Limit number of characteres that a username can contain  */
#define USERNAME 20 
/* Limit number of characteres that a task's description can contain */
#define DESCFORTASK 50 
/* Limit number of characteres that an activitie's description can contain */
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
int count_activities = 0;
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
void tasksList(int ids_introduced, int ids_introduced_list[]);
void timeAdder(int duration);
void newUser(char user[], int user_introduced);
void moveTask(int id, char newuser[], char newactivity[]);
void allTasksList(char newactivity[]);
void addActivity(char activity[], int activity_introduced);

void exch(task_t sort[], int i, int j);
int lessForStrings(char first[], char second[]);
int partitionForStrings(task_t sort[], int l, int r);
void quicksort(task_t sort[], int l, int r);
int lessForInt(int first, int second);
void insertion(task_t sort[], int l, int r);

void defaultActivities();

int main() {
	int duration, id, quit = 0;
	int ids_introduced, user_introduced, activity_introduced, ids_introduced_list[MAXTASKS];
	char command, newdescription[DESCFORTASK+1], newuser[USERNAME+1], newactivity[DESCFORACTIV+1];	
	defaultActivities();
	while (!quit) {
		command = getchar();
		switch (command) {
			case 't':
				duration = readT(newdescription);			
				newTask(duration, newdescription); 
				break;
			case 'l':
				ids_introduced = readL(ids_introduced_list);
				tasksList(ids_introduced, ids_introduced_list);
				break;
			case 'n':
				duration = readN();
				timeAdder(duration);
				break;
			case 'u':
				user_introduced = readU(newuser);			
				newUser(newuser, user_introduced);
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
				activity_introduced = readA(newactivity);
				addActivity(newactivity, activity_introduced);
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

/**************************************************************************************************
*																                                  *
*    					               READ FUNCTIONS			 								  *
*																								  *
************************************************************************************************ */

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
	int i, duration=0, index=0, negative = 1, reading_desc=0, start_num=0, end_num=0;
	char c;	
	for (i=0; (c=getchar()) != EOF && c != '\n'; i++) {	
		if ((c == ' ' || c == '\t') && !start_num && !reading_desc) {
			continue;
		} 
		else if (c == '-' && !start_num && !reading_desc) {
			negative = -1;
		}
		else if (c>='0' && c <= '9' && !end_num) {
			start_num = 1;
			duration = duration * 10 + (c - '0');
		}
		else if ((c=='.' || c==',') && start_num && !reading_desc) {
			negative = -1;
		}
		else if ((c == ' ' || c == '\t') && start_num && !reading_desc) {
			end_num = 1;	
		}	
		else if (end_num && index <= DESCFORTASK) {
			newdescription[index++] = c;
			reading_desc = 1;
		}		
	}
	newdescription[index] = '\0';
	return duration*negative;
}

int readL(int ids_introduced_list[]) {
	/*
	* Function:  readL
	* --------------------
	* Reads a list of id's asked to print the respective task
	*
	* ids_introduced_list: list of id's introduced 
	*
	* returns: the amount of id's introduced        
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
			ids_introduced_list[index++] = id*negative;
			id = 0;	
			reading = 0;
			negative=1;
		}
		else if (!reading && (c == ' ' || c == '\t')){			
			continue;
		}			
	}
	ids_introduced_list[index++] = id*negative;
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
		if (c >= '0' && c <= '9' && !end) {
			time = time * 10 + (c - '0');
			reading = 1;
			num_found = 1;
		}
		else if ((c == ' ' || c == '\t') && !reading && !end && !failed){
			continue;
		}
		else if ((c == ' ' || c == '\t') && !failed) {
			end = 1;
		}
		else if (!failed){
			failed = 1;
		}
	}
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
	int id=0, u_index=0, a_index=0, reading=0, a_found=0, id_read=0, u_read=0, a_read=0, negative=1;
	char c;
	
	while ((c=getchar()) != EOF && c != '\n') {	
		if ((c == ' ' || c == '\t') && !id_read && !u_read && !a_read && !reading) {
			continue;
		}
		else if (c=='-' && !id_read && !u_read && !a_read && !reading) {
			negative = -1;
		}
		else if (c>='0' && c <= '9' && !id_read && !u_read && !a_read) {
			reading = 1;
			id = id * 10 + (c - '0');
		}
		else if ((c == ' ' || c == '\t') && reading && !id_read && !u_read && !a_read) {
			reading = 0;
			id_read = 1;	
		}
		else if (c != ' ' && id_read && !u_read && u_index <= USERNAME && !a_read) {
			reading = 1;
			newuser[u_index++] = c;
		}
		else if ((c == ' ' || c == '\t') && id_read && !a_read && !a_found) {
			reading = 0;
			u_read = 1;
		}		
		else if (id_read && u_read && a_index <= DESCFORACTIV) {
			newactivity[a_index++] = c;
			reading = 1;
			a_found = 1;
		}		
	}
	newuser[u_index] = '\0';
	newactivity[a_index] = '\0';
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
		if ((c == ' ' || c == '\t') && !a_found) {
			continue;
		}		
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
	* Adds a new task to the system
	*
	* newactivity: the new activity's name 
	*
	* returns: if there's an activity introuced
	*           
	*/
	int a=0,a_found=0, exist_activity=0;
	char c;	
	while ((c=getchar()) != EOF && c != '\n') {	
		if ((c == ' ' || c == '\t') && !a_found) {
			continue;
		}		
		else if (a <= DESCFORACTIV) {
			newactivity[a++] = c;
			exist_activity=1;
			a_found = 1;
		}		
	}
	newactivity[a] = '\0';
    return exist_activity;
}

/**************************************************************************************************
*																                                  *
*    					               EXECUTE FUNCTIONS		 								  *
*																								  *
************************************************************************************************ */

void newTask(int duration, char newdescription[]) {
	/*
	* Function:  newTask
	* --------------------
	* Creates a new task
	*
	* duration (int): new task's duration
	* newdescription (char[]): new task's description       
	*           
	*/
	int i, index;
	if (count_tasks + 1 > MAXTASKS ) {
		printf("too many tasks\n");
		return;
	} 
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
	index = count_tasks-1;	
	tasks_list[index].id = count_tasks;
	strcpy(tasks_list[index].description, newdescription);
	strcpy(tasks_list[index].activity_name, "TO DO");
	tasks_list[index].duration = duration;
	tasks_list[index].start_time = 0;
	printf("task %d\n", tasks_list[index].id);
	return;
}

void tasksList(int ids_introduced, int ids_introduced_list[]) {
	/*
	* Function:  tasksList
	* --------------------
	* Lists all tasks
	*
	* Input  -> ids_introduced (int): number of id's introduced
	* 		 -> ids_introduced_list (int[]): array of introduced id's
	*   
	*/
	int i, j, index;
	task_t sort[MAXTASKS];	
	if (ids_introduced==0) {
		for (i=0; i < count_tasks; i++) {
			sort[i] = tasks_list[i];
		}		
		quicksort(sort, 0, count_tasks-1);
		for (i=0; i < count_tasks; i++) {
			printf("%d %s #%d %s\n",sort[i].id, sort[i].activity_name, 
				sort[i].duration, sort[i].description);
		}
		return;
	}
	for (i=0; i < ids_introduced; i++) {
		if (!(ids_introduced_list[i] <= count_tasks && ids_introduced_list[i] > 0)) {
			printf("%d: no such task\n", ids_introduced_list[i]);
		}
		else {
			for (j=0; j < count_tasks; j++) {			
				if (ids_introduced_list[i] == tasks_list[j].id) {
					index=ids_introduced_list[i]-1;
					printf("%d %s #%d %s\n",tasks_list[index].id, tasks_list[index].activity_name, 
						tasks_list[index].duration, tasks_list[index].description);
				}
			}			
		}
	}	
	return;
}

void timeAdder(int duration) {
	/*
	* Function:  timeAdder
	* --------------------
	* Advances the system's time 
	*
	* Input -> duration (int): value to add 
	*                
	*/
	if (duration < 0) {
		printf("invalid time\n");
		return;
	}
	time_now += duration;
	printf("%d\n", time_now);
	return;
}

void newUser(char newuser[], int user_introduced) {
	/*
	* Function:  newUser
	* --------------------
	* Creates a new user or displays all users
	*
	* Input  -> newuser (char[]): new user's username 
	* 		 -> user_exists (int): if any user has been introduced
	*   
	* Output -> if a new user has been created, there's no output
	*		 -> displays all existing users, if there isn't new user               
	*/
	int i, index;
	if (!user_introduced) {
		for (i=0; i < count_users; i++) {
			printf("%s\n", users_list[i].username);
		}
		return;
	}
	for (i=0; (i < count_users) && user_introduced; i++) {
		if (!(strcmp(newuser, users_list[i].username))) {
			printf("user already exists\n");
			return;
		}
	}
	if ((count_users + 1 > MAXUSERS) && user_introduced) {
		printf("too many users\n");
		return;
	}
	count_users++;
	index = count_users-1;	
	strcpy(users_list[index].username, newuser);
	return;
}

void moveTask(int id, char user[], char activity[]) {	
	/*
	* Function:  moveTask
	* --------------------
	* Moves a task from one activity to another
	*
	* Input  -> id (int): the requested task's id
	* 		 -> user (char[]): the user to be atributted to the requested task
	*		 -> activity (char[]): the destiny activity to move the requested task to
	*   
	* Output -> if moving to done, display the duration* and the slack**
	*				* duration = time spent from start (when it leaves "TO DO") 
	*							 to the end (reaches "DONE")
	*				** slack = difference between the spent time (duration) and the expected time
	*	              
	*/
    int i, valid_activity=0,valid_user=0, index;
	index = id-1;
	if (!(strcmp(tasks_list[index].activity_name, activity))) {
		return;
	}
    if (!(id <= count_tasks && id>0)) {
        printf("no such task\n");
        return;
    }	
	if (!(strcmp(activity, "TO DO"))) {
		printf("task already started\n");
		return;
	}
    for (i=0; i < count_users; i++) {
        if (!strcmp(user, users_list[i].username)) {
			valid_user = 1;	
            break;	
        }
    }
	if (!valid_user) {
		printf("no such user\n");
		return;
	}
    for (i=0; i < count_activities; i++) {
        if (!(strcmp(activity, activities_list[i].name))) {
			valid_activity = 1; 
            break;       
        }
    }
	if (!valid_activity) {
		printf("no such activity\n");
    	return;
	}
	if (!(strcmp(tasks_list[index].activity_name, "TO DO"))) {
		tasks_list[index].start_time = time_now;	
	}
	strcpy(tasks_list[index].activity_name, activity);
	strcpy(tasks_list[index].username, user);
    if (!(strcmp(activity, "DONE"))) {
        printf("duration=%d slack=%d\n", (time_now - tasks_list[index].start_time), 
			((time_now - tasks_list[index].start_time) - tasks_list[index].duration));
    }
	return;
}

void allTasksList(char activity[]) {
	/*
	* Function:  allTasksList
	* --------------------
	* Lists all tasks assinged to one activity
	*
	* Input  -> activity (char[]): the destiny activity to move the requested task to
	*   
	* Output -> for eack task, displays the id, start time (instant it leaves "TO DO") and description
	*    
	*/
	int i, valid_acivity=0;
	task_t sort_activitie_tasks[MAXTASKS];
	int n=-1;
	for (i=0; i < count_activities; i++) {
		if (!(strcmp(activity, activities_list[i].name))) {
			valid_acivity = 1;
			break;
		}
	}
	if (!valid_acivity) {
		printf("no such activity\n");
		return;
	}
	for (i=0; i < count_tasks; i++) {
		if (!strcmp(activity, tasks_list[i].activity_name)) {
			sort_activitie_tasks[++n] = tasks_list[i];
		}
	}
	quicksort(sort_activitie_tasks, 0, n); 
    insertion(sort_activitie_tasks, 0, n);
	for (i=0; i <= n; i++) {
		printf("%d %d %s\n", sort_activitie_tasks[i].id, sort_activitie_tasks[i].start_time, 
			sort_activitie_tasks[i].description);
	} 	
	return;
}

void addActivity(char newactivity[], int activity_introduced) {
	/*
	* Function:  addActivity
	* --------------------
	* Creates a new activity or displays all existing activities
	*
	* Input  -> newactivity (char[]): tthe new activity's name
	*		 -> activity_introduced (int): if there's a new activity to be created
	*   
	* Output -> nothing if a new activity is created
	* 		 -> all activities sorted by start time*
	*		    *if 2 or more activities have the same start time, they will be sorted alphabetically
	*    
	*/
	int i, len = strlen(newactivity);
	int index;
	if (!activity_introduced) {
		for (i=0; i < count_activities; i++) {
			printf("%s\n", activities_list[i].name);
		}
		return;
	}
    for (i=0; i < count_activities; i++) {
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
	if (count_activities + 1 > MAXACTIVS) {
		printf("too many activities\n");
		return;
	}	
	count_activities++;
	index = count_activities - 1;	
	strcpy(activities_list[index].name, newactivity);
	return;
}

/**************************************************************************************************
*																                                  *
*    					               SORT FUNCTIONS			 								  *
*																								  *
************************************************************************************************ */

void exchange(task_t sort[], int i, int j) {
	/*
	* Function:  exchange
	* --------------------
	* Changes the position of 2 tasks
	*
	* Input  -> sort (task_t[]): list of tasks to sort
	*		 -> i, j (int): array's indexes
	*    
	*/
	task_t aux;
	aux = sort[i];
	sort[i] = sort[j];
	sort[j] = aux; 
}

int lessForStrings(char first[], char second[]) {
	/*
	* Function:  lessForStrings
	* --------------------
	* Compares two strings
	*
	* Input  -> first, second (char[]): strings to be compared 
	*   
	* Output -> if first is less than second
	*    
	*/
	return 1 ? (strcmp(first,second)<0) : 0;
}

int partitionForStrings(task_t sort[], int l, int r) {
	/*
	* Function:  partitionForStrings
	* --------------------
	* Adapted algorithm from the partition algorithm
	*
	* Input  -> sort (task_t[]): list of tasks to sort
	*		 -> l (int): left limit
	*		 -> r (int): right limit
	*   
	* Output -> the array's index were it was split
	*    
	*/
	int i = l-1; 
	int j = r; 
	char aux[DESCFORTASK+1];
	strcpy(aux,sort[r].description); 
	while (i < j) { 				
		while (lessForStrings(sort[++i].description, aux));				
		while (lessForStrings(aux, sort[--j].description)) 
			if (j == l) 
				break;
		if (i < j)
			exchange(sort, i, j); 
	}
	exchange(sort, r, i);
	return i; 
}

void quicksort(task_t sort[], int l, int r) {
	/*
	* Function:  quicksort
	* --------------------
	* Quicksort algorithm
	*
	* Input  -> sort (task_t[]): list of tasks to sort
	*		 -> l (int): left limit
	*		 -> r (int): right limit
	*    
	*/
	int i;
	if (r <= l)
		return;
	i = partitionForStrings(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}


int lessForInt(int first, int second) {
	/*
	* Function:  lessForInt
	* --------------------
	* Adapted algorithm from the partition algorithm
	*
	* Input  -> first, second (int): integers to be compared 
	*   
	* Output -> if first is less than second
	*    
	*/
	return 1 ? (first<second) : 0;
}

void insertion(task_t sort[], int l, int r) {
	/*
	* Function:  insertion
	* --------------------
	* Adapted algorithm from the insertion algorithm
	*
	* Input  -> sort (task_t[]): list of tasks to be sorted
	*		 -> l (int): left limit
	*		 -> r (int): right limit
	*    
	*/
	int i,j;
	task_t aux;
	for (i = l+1; i <= r; i++) {
		aux = sort[i];
		j = i-1;
		while ( j>=l && lessForInt(aux.start_time, sort[j].start_time)) {
			sort[j+1] = sort[j];
			j--;
		}
	sort[j+1] = aux;
	}
}

/******************************************************************
*																  *
*    					AUXILIAR FUNCTIONS						  *
*																  *
**************************************************************** */

void defaultActivities() {
	count_activities = 3;		
	strcpy(activities_list[0].name, "TO DO");
	strcpy(activities_list[1].name, "IN PROGRESS");
	strcpy(activities_list[2].name, "DONE");
}