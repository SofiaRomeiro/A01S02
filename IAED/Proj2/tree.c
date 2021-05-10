#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "tree.h"
#include "directory.h"
#include "structs.h"



#define ROOT "/"



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

void treeAdd(tree_node_s root, input_s newinput) {  

    directory test;

    /* guardar o endereço da root sempre, so mexer no node*/
    tree_node_s node = root; 

    /* first new_input node is empty */
    test = newinput->path->next;

    printf("[treeAdd] value: %s\n", newinput->value);
    printDir(newinput->path);  
    

    /*por cada dir no new input*/

            /* ver se existe o dir, se nao existe criar c o nome lido */


            // for child in node (&& not found)
                // strcmp(child->path, dir) ==
                    // node = child
                    // found 
            
            // if not found
                // create child
                // add child to node (parent)
                // node = child   

         /*   
        }
    }
    */

    destructorI(newinput);
}


/* TODO tree_modify */
/* TODO tree_delete */
/* TODO tree_search */
/* TODO tree_find */
/* TODO tree_list */

