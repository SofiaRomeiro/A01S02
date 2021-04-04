#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./usecases.h"

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

	tasks_list[id_num-1].duration = duration;
	tasks_list[id_num-1].start_time = 0;
	
	/* saida : task <id> */	
	printf("task %d\n", tasks_list[id_num-1].id);

/*	printf("duration : %d\n", tasks_list[id_num-1].duration);
	printf("sentence: %s\n", tasks_list[id_num-1].description); */

	return 0;
}

void tasksList(int ids[], int id_counter) {

	int i;
	for (i=0; i < id_counter; i++) {
		printf("id : %d\n", ids[i]);
	}
	printf("number of id's : %d\n", id_counter);
}

void timeAdder(int duration) {
	printf("duration : %d\n", duration);
}

void newUser(char newuser[], int user_exist) {
	printf("user : %s\n", newuser);
	printf("%s\n", user_exist ? "user exist" : "user does not exist");
}

void moveTask(int id, char newuser[], char newactivity[]) {
	printf("id :%d\nuser: %s\nactivitie: %s\n", id, newuser, newactivity);
}

void allTasksList(char newactivity[]) {
	printf("activity : %s", newactivity);
}

void addActivity(char newactivity[], int activ_exist) {
	printf("exist: %d\nactivity: %s\n", activ_exist, newactivity);
}