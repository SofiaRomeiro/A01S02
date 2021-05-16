#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


list_s initList() {
    list_s new;
    new = (list_s) malloc(sizeof(struct list));
    new->current = NULL;
    new->next = NULL;
    new->previous= NULL;
    return new;
}

list_s insertBegin(list_s head, tree_node_s node)
{
    list_s new = (list_s) malloc(sizeof(struct list));
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

void printList(list_s head) {
    list_s t = head;
    
    for(t = head; t != NULL; t = t->next) {
        if (t->current != NULL) {
            printf("/%s", t->current->path);
        }
        else {
            printf("\n");
            return;
        }
    }
    
}

list_s removeBegin(list_s head) {
    list_s prev=NULL, curr=head;
    curr = prev->next;
    prev->next = curr->next;
    return curr;
}

void removeEnd(list_s head) {

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



struct node* init(){
    struct node *top = NULL;
    return top;
}

void destroyStack(node_s stack) {

    node_s aux;

    while (stack != NULL) {
        aux = stack;
        stack = stack->next;
        free(aux);
    }

}

node_s push(tree_node_s adding, node_s top){
    struct node *new;
    new = (struct node *) malloc(sizeof(struct node));
    new->current = adding;
    new->next = top;
    top = new;
    return top;
}

int is_empty(node_s top){
    return top == NULL;
}

node_s pop(node_s top) {
    struct node *old;

    if (!is_empty(top)) {
        old = top;
        top = top->next;
        free(old);
        return top;
    }
    else
        return NULL;
}


