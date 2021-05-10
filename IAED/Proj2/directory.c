#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"
#include"structs.h"

#define MAX_BUFFER 65535



input_s constructorI() {
    input_s new_input = (input_s) malloc(sizeof(struct input));
    new_input->path = NULL;
    new_input->value = NULL;

    return new_input;
}

directory constructorD() {
    directory new_dir = (directory) malloc(sizeof(struct dir));
    new_dir->name = NULL;
    new_dir->next = NULL;

    return new_dir;
}

void destructorD(directory dir) {

    directory current, next;
    for (current = dir; current != NULL; current = next) {
        next = current->next;
        free(current);
    }
}

void destructorI(input_s input) {
    if (input->value != NULL) {
        free(input->value);
    }
    destructorD(input->path);
    free(input);
}

void push(char *dir, directory head) {
    directory new;

    new = (directory) malloc(sizeof(struct dir));
    new->name = (char *) malloc(sizeof(char)*(strlen(dir)+1));
    strcpy(new->name, dir);
    new->next = head;
    head = new;
}

directory insertBegin(directory head, char buffer[]) {
    directory new = (directory) malloc(sizeof(struct dir));
    new->name = (char *) malloc(sizeof(char)* (strlen(buffer)+1));
    strcpy(new->name, buffer);
    new->next = head;
    /* new will be the current head */
    return new;
}

directory insertEnd(directory head, char buffer[]){
    directory temp;
    directory new = (directory) malloc(sizeof(struct dir));
    new->name = (char *) malloc(sizeof(char)* (strlen(buffer)+1));
    strcpy(new->name, buffer);
    new->next = NULL;
    if(head == NULL) return new;
    for(temp = head; temp->next != NULL; temp = temp->next)
    ;
    temp->next = new;
    return head;
}

input_s newPath(char path[], directory head) {
    int i, j=0, len = strlen(path);  
    char c,buffer[20];
    directory newdir;
    input_s newinput;

    for (i=0; i <= len; i++) {
        if ((c = path[i]) == '/' || c == ' ' || c == '\0') {

            if (strlen(buffer) > 1) {
                buffer[j] = '\0';
                j = 0;
                newdir = insertEnd(head, buffer);
                head = newdir;
                buffer[0] = '\0';               
            }
            if (c== ' ') {
                newinput = newInput(head, i, path, len);
                return newinput;
            }
        }       

        else {
            buffer[j++] = path[i];
        }
    }

    return newinput;
} 

void printInput(input_s input) {
    printf("[printInput] value: %s\n", input->value);
    printDir(input->path);
}

void printDir(directory head) {
    for (head=head->next; head != NULL; head = head->next) {
        printf("[printDir] %s\n", head->name);
    }
}

input_s newInput(directory head, int pos_vec, char path[], int len_buffer) {

    input_s new_input = constructorI();
    char c, value_t[MAX_BUFFER];
    int i=0, found=0;

    /* TODO tirar espaços finais do value e contar com tabulador para value*/

    for (; pos_vec <= len_buffer && (c=path[pos_vec]) != '\0'; pos_vec++) {
        if ((c == ' ')  && !found) {
            continue;
        }
        else {
            found = 1;
            value_t[i++] = c;
        }
    }
    value_t[i] = '\0';

    new_input->path = head;
    new_input->value = (char*) malloc(sizeof(char)*(strlen(value_t)+1));
    strcpy(new_input->value, value_t);

    return new_input;
}

