#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 1023

typedef struct stru_node {
    struct stru_node *next;
    char *v;
} node;

node *pop(node *head) {

    node *old;
    old = head; /* head assigned to old */
    head = head->next; /* new head will be the next struct that followed the older head*/
    free(old->v);
    free(old);
    return head;
}

node *push(node *head, char *buffer) {

    node *new = (node *)malloc((sizeof(node)));
    new->v = (char *)malloc(sizeof(char)*(strlen(buffer)+1));
    strcpy(new->v,buffer);
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

    int size = strlen(head->v);
    while (size > 0) {
        printf("%c", head->v[--size]);
    }
    printf("\n");
    pop(head);    
}

int main() {

    char c;
    int size=0;

    char buffer[MAX_LEN];
    node *list = NULL;    

    while ((c=getchar()) != 'x' && size != 1023) {
        buffer[size++] = c;
    }
    list = push(list, buffer);

    print(list); 

    return 0;
}