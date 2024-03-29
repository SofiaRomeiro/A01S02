#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stru_node {
    struct stru_node *next;
    int v;
} node;

node *pop(node *head) {

    node *old;
    old = head; /* head assigned to old */
    head = head->next; /* new head will be the next struct that followed the older head*/
    free(old);
    return head;
}

node *push(node *head, int e) {

    node *new;
    new = (node *)malloc((sizeof(node)));
    new->v = e;
    new->next=head;
    return new;
}

node *destroy(node *head) {
    node *destroy;
    while (head != NULL) {
        destroy = head;
        head = head->next;
        free(destroy);
    }
    return NULL;
}

void print(node *head) {
    node *i;
    for (i=head; i != NULL; i=i->next) {
        printf("%d\n", i->v);
    }
}

int main() {

    return 0;
}


