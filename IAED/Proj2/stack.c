#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


list_node_s insertEnd(list_ext_s extremes, list_node_s head, tree_node_s tree_node) {
    /* criar o novo node */
    list_node_s new = (list_node_s)malloc(sizeof(struct list_node));
    new->node = tree_node;
    new->next = NULL;
    /* verificar o estado dos extremes */
    if (extremes->head == NULL) {
        /* adicionar aos extremos */
        extremes->head = new;
        extremes->tail = new; /* o elemento é a sua propria tail*/        
        /* adicionar à head */
        new->next = NULL;
        head->next = new;
        new->previous = head;
        return new;
    }

    else {
        /* nova tail é o meu node */
        extremes->tail = new;
        /* adicionar à head */
        new->previous = head;
        head->next = new;
        new->next = NULL;      
        return new;
    }
    return NULL;
}

list_node_s deleteEnd(list_ext_s extremes, list_node_s head) {

    list_node_s to_free, newtail;

    if (head == NULL) {
        return NULL;
    }  
    
    to_free = head;
    newtail = head->previous;
    newtail->next = NULL;
    extremes->tail = newtail;
    free(to_free);
    return newtail;
}

void printList(list_ext_s extremes) {
    list_node_s aux=extremes->head;
    while (aux != NULL) {
        printf("/%s",aux->node->path); 
        aux = aux->next; 
    }
    printf(" %s\n", extremes->tail->node->value);    
}

void printSearch(list_ext_s extremes) {
    list_node_s aux=extremes->head;
    while (aux != NULL) {
        printf("/%s\n",aux->node->path); 
        aux = aux->next; 
    }
    return;
}



void destroyList(list_ext_s extremes) {
    list_node_s head = extremes->head, to_free;
    while (head != NULL) {
        to_free = head;
        head = head->next;
        free(to_free);
    } 
}

/*
stack_s initStack(){
    stack_s top = (stack_s) malloc(sizeof(struct stack));
    top->current = NULL;
    top->next = NULL;
    top->previous = NULL;
    return top;
}

void destroyStack(stack_s stack) {  
    free(stack);
}

stack_s push(tree_node_s adding, stack_s stack){

    if (is_empty(stack)) {
        stack = (stack_s) malloc(sizeof(struct stack));
        stack->current = adding;
        stack->previous = NULL;
        stack->next = NULL;
        return stack;
    } 
    else {
        stack_s new = (stack_s) malloc(sizeof(struct stack));    
        new->current = adding;
        new->previous = NULL;
        stack->previous = new;
        new->next = stack;
        return new;
    }  
}

int is_empty(stack_s stack){
    return stack == NULL;
}

stack_s pop(stack_s top) {
    stack_s old;

    if (!is_empty(top)) {
        old = top;
        top = top->next;
        free(old);      
        return top;
    }
    else
        return NULL;
}

void printStack(stack_s stack) {  

    stack_s tail, aux=stack; 
    
    if (stack==NULL) {
        return;
    }

    while (aux->next != NULL) {           
        aux = aux->next; 

    }
    tail = aux; 

    while(tail->previous != NULL) {
       printf("/%s", tail->current->path);
       aux = tail;
       tail = tail->previous;
    }
    printf("\n");
}

void printFuncStack(stack_s stack) {     

    stack_s tail, aux=stack;
    if (stack==NULL) {
        return;
    }

    while (aux->next != NULL) {            
        aux = aux->next;        
    }
    tail = aux;

    while(tail != NULL) {
       printf("/%s", tail->current->path);
       aux = tail;
       tail = tail->previous;
    }
    printf(" %s\n", aux->current->value);    
}


int countNodes(tree_node_s root) {
    int counter;
    tree_node_s aux=root;
    for (counter=0; aux != NULL; counter++, aux = aux->brother);
    return counter;
}*/