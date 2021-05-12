#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


list_node_s listConstructor(){
    list_node_s newnode = (list_node_s) malloc(sizeof(struct list_node));
    newnode->tree_node = NULL;
    newnode->next = NULL;
    return newnode;
}

void listDestructor(list_node_s node) {
    tree_node_s current;
    list_node_s aux=node;
    for (current = node->tree_node; aux != NULL; current = aux->next) {
        aux->next = current;
        treeDestructor(current);
    }
}

tree_node_s listSearch(list_node_s children_list, char *target_dir) {

    tree_node_s previous = children_list->tree_node;

    while (children_list->tree_node != NULL) {
         if (children_list->tree_node->path != NULL && !strcmp(children_list->tree_node->path, target_dir)) {
            // nó que contem o target dir procurado
            return children_list->tree_node;
        }
        previous = children_list->tree_node;
        children_list->tree_node = children_list->next;
          
    }

    if (children_list->tree_node == NULL) {
        return previous;
    }
    
    return children_list->tree_node;
}



/* TODO list_add */
/* TODO list_modify */
/* TODO list_delete */
/* TODO list_search */
/* TODO list_find */

tree_node_s listFind(list_node_s children, char *target_dir) {

    tree_node_s current = children->tree_node;

    for (; current != NULL; current = children->tree_node) {
        if (current->path != NULL && !strcmp(current->path, target_dir)) {
            return current;
        }
        children->tree_node = children->next;            
    }
    
    return current;
}

/* TODO list_list */

