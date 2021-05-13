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
    tree_node_s current=node->tree_node;
    for (current = node->tree_node; current != NULL; current = node->next) {
        current=node->next;
        free(node->tree_node);
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
    return children_list->tree_node;
}


list_node_s isItBrother(list_node_s children_list) {
    // return do local onde se deve inserir o proximo filho
    list_node_s previous_node;

    while (children_list->tree_node != NULL) {
        previous_node = children_list->tree_node;
        children_list->tree_node = children_list->next;
    }
    
    return previous_node;
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
