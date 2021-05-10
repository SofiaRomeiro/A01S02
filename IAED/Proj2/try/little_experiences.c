#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dir {
    char *name;
    struct dir *next;
} *directory;

directory constructor() {
    directory new_dir = (directory) malloc(sizeof(struct dir));
    new_dir->name = NULL;
    new_dir->next = NULL;

    return new_dir;
}

void destructor(directory dir) {

    directory current, next;
    for (current = dir; current != NULL; current = next) {
        next = current->next;
        free(current->next);
        free(current);
    }
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

directory newPath(char path[], directory head) {
    int i, j=0, len = strlen(path);  
    char c,buffer[20];
    directory new;



    for (i=0; i <= len; i++) {
        if ((c = path[i]) == '/' || c == ' ' || c == '\0') {

            if (strlen(buffer) > 1) {
                buffer[j] = '\0';
                j = 0;
                new = insertEnd(head, buffer);
                head = new;
                buffer[0] = '\0';                
            }
        }

        else {
            buffer[j++] = path[i];
        }
    }

    return head;
} 



int main() {

    char path[100];

    directory head = constructor();
    directory copyhead;

    strcpy(path, "/usr/local/bin/ncinfo/voadores");    

    copyhead = newPath(path, head);

    for (copyhead=copyhead->next; copyhead != NULL; copyhead = copyhead->next) {
        printf("%s.\n", copyhead->name);
    }

    destructor(copyhead);

    return 0;
}