#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "list.h"

#define ROOT "/"

struct tree_node {
    char *path;
    char *value;
    list_node_s childs; 
};


/* TODO tree_constructor */

tree_node_s treeConstructor(){
    tree_node_s new_tree = (tree_node_s)malloc(sizeof(struct tree_node));
    new_tree->value = NULL;
    new_tree->path = (char *)malloc(sizeof(char)*strlen(ROOT)+1);
    strcpy(new_tree->path, ROOT);
    new_tree->childs = NULL;
    return new_tree;
}

/* TODO tree_destructor */
void treeDestructor(tree_node_s node) {
    if (node->childs != NULL) {
        listDestructor(node->childs);
    }
    if (node->path != NULL) {
        free(node->path);
    }
    if (node->value != NULL) {
        free(node->value);
    }
    free(node);
}

/* TODO treeAdd */

void treeAdd(tree_node_s root, char *path, char *value ) {

    int i;
    int len  = strlen(path);

    char c;
    /* TODO experimentar sem malloc */
    char *dir = (char *) malloc(sizeof(char)*(len+1));

    tree_node_s node = root;    

    for (i = 0; (c=path[i]) != '\0'; i++) {
        if (c == '/') {

            dir[i] = '\0';
            /* ver se existe o dir, se nao existe criar c o nome lido */

            // for child in node (&& not found)
                // strcmp(child->path, dir) ==
                    // node = child
                    // found 
            
            // if not found
                // create child
                // add child to node (parent)
                // node = child   

            i = 0;
        }
        else {
            dir[i] = c;

        }
    }

    free(dir);
}


/* TODO tree_modify */
/* TODO tree_delete */
/* TODO tree_search */
/* TODO tree_find */
/* TODO tree_list */

