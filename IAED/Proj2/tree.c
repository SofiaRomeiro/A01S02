#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

#define ROOT "/"
#define MAX_PATH 65529

tree_node_s treeConstructor(){
    tree_node_s new_tree = (tree_node_s)malloc(sizeof(struct tree_node));
    new_tree->value = NULL;
    new_tree->path = (char *)malloc(sizeof(char)*strlen(ROOT)+1);
    strcpy(new_tree->path, ROOT);
    new_tree->childs = NULL;
    return new_tree;
}

tree_node_s newTreeNode() {
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node));
    new_node->value = NULL;
    new_node->path = NULL;
    new_node->childs = NULL;
    return new_node;
}


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



void treeAdd(tree_node_s root, char buffer[]) {  
    /* guardar o endereço da root sempre, so mexer no node*/
    tree_node_s parent = root;
    int i, j=0, found=0, len = strlen(buffer); 
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];
    //por cada dir no new input (cada dir tem um "parent" correspondente)     
    for (i=0; i < len; i++) {
        if ((c = buffer[i]) == '/' || c == ' ' || c == '\0') {
            directory[j] = '\0';             

            if (strcmp(directory,"") && strcmp(directory, "/")) {         
                j = 0;               
                printf("directory: %s\n", directory);               
                parent = auxAddTree(parent, directory); 
                directory[0] = '\0';       
                printf("[treeAdd]path %s\n", parent->path);          
            }
            else {
                j = 0;
                directory[0] = '\0'; 
            }
            if (c== ' ') {                
                break;
            }
        }     
        else {
            directory[j++] = buffer[i];
        }
        
    }
    // quando o dir for NULL, chegámos ao fim, e o value pode ser adicionado ao ultimo child (acabar de ler o value do buffer, aproveitar o valor do i)  
    for (; i < len; i++) {
        if (buffer[i] == ' ' && !found) { 
        }  
        else {
            found = 1;
            value[j] = buffer[i];
            j++;          
        }
    }
    value[j] = '\0';

    parent->value = (char *)malloc(sizeof(char)*(strlen(value)+1));
    strcpy(parent->value, value);
    printf("[treeAdd] path : %s | value : %s\n", parent->path, parent->value);
}

tree_node_s auxAddTree(tree_node_s parent, char directory[]) {

    // ver se existe o parent, se nao existe criar c o dir 
    tree_node_s aux = parent;  
    if (aux->childs != NULL) {
        // usar função que pesquisa a lista e devolve o novo parent (node com o nome do dir);
        aux = listSearch(aux->childs, directory);
        if (aux == NULL) {
            parent = newChild(parent, directory);
            return parent;
        }
        return aux;
    }
    parent = newChild(parent, directory);
    return parent;
}

tree_node_s newChild(tree_node_s parent, char directory[]) {
    tree_node_s child;
    list_node_s children;
    // create child
    child = newTreeNode();
    child->path = (char *) malloc(sizeof(char)*(strlen(directory)+1));
    strcpy(child->path, directory);                      
    // add child to node (parent) - create children list
    children = listConstructor();
    children->tree_node = child;
    parent->childs = children;
    parent = child;
    return parent;
}


/* TODO tree_print */

void treePrint(tree_node_s root) {

}
/* TODO tree_delete */
/* TODO tree_search */
/* TODO tree_find */

void treeFind(tree_node_s root, char buffer[]) {
    // ERROS :
        // not found
        // no data
    read(buffer);
    printf("[treeFind] buffer : %s\n", buffer);
}
/* TODO tree_list */

