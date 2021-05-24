#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


list_node_s insertEnd(list_ext_s tail, list_node_s head, tree_node_s tree_node) {
    /* criar o novo node */
    list_node_s new = (list_node_s)malloc(sizeof(struct list_node));
    new->node = tree_node;
    /* verificar o estado dos extremes */
    
    
    if (head == NULL) {
        head = (list_node_s)malloc(sizeof(struct list_node));
        head = new;
        head->previous = NULL;
        head->next = NULL;
        tail->list_node = new;  
        printf("[insertEnd]head NULL? %d\ntail NULL? %d\n", head==NULL, tail==NULL);        
        return head;
    }

    else {
        head->next = new;
        new->previous = head;
        new->next = NULL;
        head = new;
        return head;
    }
    return NULL;
}

list_node_s deleteEnd(list_ext_s tail, list_node_s head) {

    list_node_s to_free, new_head;

    if (head == NULL) {
        return NULL;
    }  
    
    if (!strcmp(tail->list_node->node->path, head->node->path)) {
        tail->list_node = NULL;
    }
    to_free = head;
    new_head = head->previous;
    new_head->next = NULL;
    free(to_free);
    return new_head;
}

void printList(list_ext_s head) {
    list_node_s current = head->list_node;
    list_node_s previous=NULL;
    while (current != NULL) {
        printf("/%s",current->node->path); 
        previous = current;
        current = current->next; 
    }
    printf(" %s\n", previous->node->value);    
}

void printSearch(list_ext_s head) {
   
    list_node_s current = head->list_node;
    
    while (current != NULL) {        
        printf("/%s",current->node->path);
        current = current->next; 
    }
    
    printf("\n");
    return;
}



void destroyLinkedList(list_ext_s head) {
    list_node_s to_free = head->list_node;
    while (to_free != NULL) {
        to_free = deleteEnd(head, to_free);
    } 
}

