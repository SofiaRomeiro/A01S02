#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

typedef struct input* input_s;
typedef struct dir* directory;

input_s newInput(directory head, int pos_vec, char buffer[], int len_buffer);

directory constructorD();
void destructorD(directory dir);

input_s constructorI();

void push(char *dir, directory head);
directory insertBegin(directory head, char buffer[]);

directory insertEnd(directory head, char buffer[]);
input_s newPath(char path[], directory head);

void printDir(directory head);
void printInput(input_s input);
void destructorI(input_s input);

#endif

