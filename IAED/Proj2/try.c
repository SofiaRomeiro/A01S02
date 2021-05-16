#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

// ***********  LIST  *******************



struct list {
    struct tree_node *current;
    struct list *previous, *next;
};

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

tree_node_s treeSearch(tree_node_s root, char buffer[], node_s top) {
    tree_node_s aux = root;
    node_s stack = top;
    // fim -> o parent é NULL  
    if (aux == NULL) {        
        return NULL;
    }

    // encontrou o valor, PARA tudo! 
    if (aux->value != NULL && !strcmp(aux->value, buffer)) {
        Printer(stack); 
        return NULL;
    } 

    // tem filhos ? 
        // sim! passa para o proximo filho
    else if (aux->child != NULL) {
        stack = push(aux->child, stack);
        return treeSearch(aux->child, buffer, stack);
    }

    // não! passa para o irmao
    else if (aux->brother != NULL) {

        stack = pop(stack);       
        stack = push(aux->brother, stack);
        return treeSearch(aux->brother, buffer, top);
    }

     // tem irmao e nao tem filhos?      
    else {
        // nao! volta para o parent e passa para o proximo irmao do parent 
        if (aux->parent->brother == NULL) {
            stack = pop(stack);
            printf("not found\n");
            return NULL;
        }
        // sim! passa para o irmao 
        else {
            stack = pop(stack);
            stack = pop(stack);
            stack = push(aux->parent->brother, stack);

            return treeSearch(aux->parent->brother, buffer, stack);
        }
    }    
}   

void Printer(node_s top) {
    list_s list = initList();
    node_s node = top;

    while (node != NULL) { 
        list = insertBegin(list, node->current);
        node = node->next;
        
    }
    printf("\n");
    printList(list);
    free(list);
    destroyStack(top);
}

