#ifndef __USECASES_H__
#define __USECASES_H__ 1

#include "./define.h"

int newTask(int duration, char description[], int id_num, task_t tasks_list[]);
void tasksList(int ids[], int id_counter);
void timeAdder(int duration);
void newUser(char user[], int user_exist);
void moveTask(int id, char user[], char activity[]);
void allTasksList(char activities[]);
void addActivity(char activity[], int activ_exist);

#endif