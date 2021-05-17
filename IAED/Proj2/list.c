#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


// *********  STACK  *****************

stack_s initStack(){
    stack_s top = (stack_s) malloc(sizeof(struct stack));
    top->current = NULL;
    top->next = NULL;
    top->previous = NULL;
    return top;
}

void destroyStack(stack_s stack) {

    stack_s aux;

    while (stack != NULL) {
        aux = stack;
        stack = stack->next;
        free(aux);
    }
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
        new->next = stack;
        stack->previous = new;
        return new;
    }  
}

int is_empty(stack_s stack){
    return stack == NULL;
}

stack_s pop(stack_s top) {
    stack_s newtop = (stack_s) malloc(sizeof(struct stack));

    if (!is_empty(top)) {
        newtop = top->next;
        free(top);
        return newtop;
    }
    else
        return NULL;
}

void printStack(stack_s stack) {    

    stack_s tail, aux=stack;
    while (aux->next != NULL) {            
        aux = aux->next;        
    }
    tail = aux;

    while(tail != NULL) {
       printf("/%s", tail->current->path);
       aux = tail;
       tail = tail->previous;
    }
    printf("\n");
}

void printFuncStack(stack_s stack) {    

    stack_s tail, aux=stack;
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



