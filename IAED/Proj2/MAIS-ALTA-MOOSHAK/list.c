#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


/* *********  STACK  ***************** */

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
}

/* *************************  QUICK SORT  ************************* */

void exchange(tree_node_s sort[], int i, int j) {

	tree_node_s aux;
	aux = sort[i];
	sort[i] = sort[j];
	sort[j] = aux; 
}

int less(tree_node_s first, tree_node_s second) {

	return 1 ? (strcmp(first->path,second->path)<0) : 0;
}

int partition(tree_node_s sort[], int l, int r) {

	int i = l-1; 
	int j = r; 
	tree_node_s aux;
	aux = sort[r]; 
	while (i < j) { 				
		while (less(sort[++i], aux));				
		while (less(aux, sort[--j])) 
			if (j == l) 
				break;
		if (i < j)
			exchange(sort, i, j); 
	}
	exchange(sort, r, i);
	return i; 
}

void quicksort(tree_node_s sort[], int l, int r) {

	int i;
	if (r <= l)
		return;
	i = partition(sort, l, r);
	quicksort(sort, l, i-1);
	quicksort(sort, i+1, r);
}


