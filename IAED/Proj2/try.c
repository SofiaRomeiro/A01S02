#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

typedef struct list * list_s;

struct list {
    tree_node_s current;
    struct node *previous, *next;
};

node_s initList() {
    list_s new;
    new = (list_s) malloc(sizeof(struct list));
    new->current = NULL;
    new->next = NULL;
    new->previous= NULL;
    return new;
}

list_s insertBegin(list_s head, tree_node_s node)
{
    list_s new = (node_s)malloc(sizeof(struct node));
    new->previous = NULL;
    new->current = node;
    new->next = head;
    //new is the new head
    return new;
}

list_s insertEnd(list_s head, tree_node_s node) {
    list_s t=head;
    list_s new = (list_s)malloc(sizeof(struct list));
    new->previous = head;
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

void removeEnd(node_s head) {

    list_s t=head, old;
    tree_node_s aux;

    // procurar o ultimo elemento
    for(t = head; t->next != NULL; t = t->next);
    aux = t->current;
    old = t->next;
    t->next = NULL;
    t->current = NULL;
    free(old);
    treeDestructor(aux);
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