#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

typedef struct node * node_s;

struct node {
    tree_node_s current;
    struct node *previous, *next;
};

node_s init() {
    node_s new;
    new = (node_s) malloc(sizeof(struct node));
    return new;
}

node_s insertBegin(node_s head, tree_node_s node)
{
    node_s new = (node_s)malloc(sizeof(struct node));
    new->current = node;
    new->next = head;
    //new is the new head
    return new;
}

node_s insertEnd(node_s head, tree_node_s node) {
    node_s t;
    node_s new = (node_s)malloc(sizeof(struct node));
    new->current = node;
    new->next = NULL;

    if(head == NULL) 
        return new;

    for(t = head; t->next != NULL; t = t->next);

    t->next = new;
    return head;
}

void printList(node_s head) {
    node_s t;
    for(t = head; t != NULL; t = t->next)
    printf("%s\n",t->current->path);
}

node_s remove(node_s head) {
    node_s prev=NULL, curr = head;
    while (curr != NULL) {
        prev = curr;
        curr = curr->next;
    }
    if (prev != NULL) /* se não for o primeiro elemento */
        prev->next = curr->next;
    else 
        head = curr->next;
        free(curr);

    return head;
}

int size(node_s head){
    int count=0;
    node_s x;
    for(x=head ; x!=NULL; x=x->next)
        count++;
    return count;
}







int main() {

    // len 11

    char *teste;
    char *pila;
    teste = (char*) malloc(sizeof(char)*12);

    strcpy(teste, "ola bom dia");

    pila = teste;

    free(pila);

    return 0;
}