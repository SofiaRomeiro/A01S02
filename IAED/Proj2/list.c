#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tree.h"
#include "structs.h"


list_node_s listConstructor(){
    list_node_s newnode = (list_node_s) malloc(sizeof(struct list_node));
    newnode->tree_node = NULL;
    newnode->next = NULL;
    return newnode;
}

void listDestructor(list_node_s node) {
    tree_node_s current, next;
    list_node_s aux=node;
    for (current = node->tree_node; aux != NULL; current = aux->next) {
        aux->next = current;
        treeDestructor(current);
    }
}

tree_node_s listSearch(list_node_s children, char *target_dir) {

    tree_node_s current = children->tree_node;

    

    for (; current != NULL; current = children->tree_node) {        

        if (current->value != NULL && !strcmp(current->value, target_dir)) {
            return current;
        }
        children->tree_node = children->next;            
    }
    
    return current;
}



/* TODO list_add */
/* TODO list_modify */
/* TODO list_delete */
/* TODO list_search */
/* TODO list_find */
/* TODO list_list */

