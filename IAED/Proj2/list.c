#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tree.h"

struct list_node {
    tree_node_s tree_node;
    list_node_s next;
};

list_node_s listConstructor(){
    return NULL;
}

void listDestructor(list_node_s node) {
    list_node_s current, next;
    for (current = node; current != NULL; current = next) {
        next = current->next;
        treeDestructor(current->tree_node);
        free(current);
    }
}

/* TODO list_add */
/* TODO list_modify */
/* TODO list_delete */
/* TODO list_search */
/* TODO list_find */
/* TODO list_list */

