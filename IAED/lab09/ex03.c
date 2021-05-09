#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1000
#define STOP_CHAR "x"

typedef struct stru_node {
    struct stru_node *next;
    char *s;
} node;

node *pop(node *head) {

    node *old;
    old = head; /* head assigned to old */
    head = head->next; /* new head will be the next struct that followed the older head*/
    free(old->s);
    free(old);
    return head;
}

node *push(node *head, char *buffer) {

    node *new = (node *)malloc((sizeof(node)));
    char *new_s = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(new_s,buffer);
    new->s = new_s;
    new->next=head;
    return new;
}

node *destroy(node *head) {

    while (head != NULL) {
        head = pop(head);
    }
    return head;
}

void print(node *head) {
    while (head != NULL) {
        printf("%s\n", head->s);
        head = head->next;
    }
}

int main() {

    char buffer[MAX_LEN];
    node *new_node = NULL; /* list of strings in "node" form */

    while ((scanf("%s", buffer))==1) {
        if (!strcmp(buffer,"x")) {
            print(new_node);
            destroy(new_node);
            return 0;
        }
        printf("buffer : %s\n", buffer);
        new_node = push(new_node, buffer);
    }  

    return 0;
}