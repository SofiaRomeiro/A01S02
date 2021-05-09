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

int is_eq(node *h1, node *h2) {

    int sz_h1=0, sz_h2=0;

    while (h1 != NULL || h2 != NULL) {
        if (h1->v != h2->v) {
            return 0;
        }
        h1 = h1->next;
        sz_h1++;
        h2 = h2->next;
        sz_h2++;
    }
    return sz_h1 == sz_h2;
}

node *rev(node *head) {
    
    node *new_head = NULL;
    while (head != NULL) {
        new_head = push(new_head, head->v);
        head = head->next;
    }
    return new_head;
}

int main() {
    return 0;
}