#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"

#define ROOT "/"
#define MAX_PATH 65529

tree_node_s treeConstructor(){
    tree_node_s new_tree = (tree_node_s)malloc(sizeof(struct tree_node));    
    new_tree->path = (char *)malloc(sizeof(char)*strlen(ROOT)+1);
    strcpy(new_tree->path, ROOT);
    new_tree->value = NULL;
    new_tree->brother = NULL;
    new_tree->child = NULL;
    new_tree->parent = NULL;
    return new_tree;
}

tree_node_s newTreeNode() {
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node));
    new_node->value = NULL;
    new_node->path = NULL;
    new_node->child = NULL;
    new_node->brother = NULL;
    new_node->parent = NULL;
    return new_node;
}


void treeDestructor(tree_node_s node) {
    free(node->path);
    free(node->value);
    free(node);
}


void treeAdd(tree_node_s root, char buffer[]) {  
    /* guardar o endereço da root sempre, so mexer no parent*/
    tree_node_s parent = root;
    tree_node_s newchild;

    int i, j=0, found=0, len = strlen(buffer); 
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];

     
    for (i=0; i < len; i++) {
        if ((c = buffer[i]) == '/' || c == ' ' || c == '\0') {
            directory[j] = '\0';           

            if (strcmp(directory,"") && strcmp(directory, "/")) {         
           
                newchild = auxAddTree(parent, directory);
                    
                newchild->parent = parent;
            
                parent = newchild;
                clear(directory);
                j=0;

            }
            else {
                j = 0;
                clear(directory); 
            }
            if (c== ' ') {
                j=0;                
                break;
            }
        }     
        else {
            directory[j++] = buffer[i];
        }
        
    }

    for (; i < len; i++) {
        if (buffer[i] == ' ' && !found) { 
        }  
        else {
            found = 1;
            value[j++] = buffer[i];         
        }
    }
    value[j] = '\0';

    
    newchild->value = (char *) malloc(sizeof(char)*(strlen(value)+1));
    strcpy(newchild->value, value);

    clear(value);
    clear(directory);   
}

tree_node_s auxAddTree(tree_node_s parent, char path[]) {

 
    tree_node_s child;
    tree_node_s brother;


    if (parent->child != NULL) {
       
        
        brother = brotherSearch(parent->child, path); 

        if (brother != NULL) {
            return brother;
        }
        else {        
            brother = findBrotherNode(parent->child);
            child = newChild(path); 
            child->parent = parent;
            brother->brother = child;
            return child;
        }
    }
    else {
        child = newChild(path);
        child->parent = parent;
        parent->child = child;
        return child;
    }
}

tree_node_s findBrotherNode(tree_node_s current){
    tree_node_s aux = current;
    while (aux->brother != NULL) {
        aux = aux->brother;
    }
    return aux;
}

tree_node_s newChild(char path[]){
    tree_node_s newchild;
    newchild = newTreeNode();
    newchild->path = (char *) malloc(sizeof(char) * (strlen(path)+1));
    strcpy(newchild->path, path);
    newchild->child = NULL;
    newchild->brother = NULL;
    newchild->parent = NULL;
    newchild->value = NULL;

    return newchild;
}

tree_node_s brotherSearch(tree_node_s child, char path[]){
    tree_node_s aux = child;
    while (aux != NULL) {
        if (!strcmp(aux->path, path)) {
            return aux;
        }
        aux = aux->brother;
    }
    return NULL;
}


tree_node_s treeSearch(tree_node_s root, char buffer[], stack_s top) {
    tree_node_s parent = root;
    stack_s stack = top;

    if (parent == NULL) {        
        return NULL;
    }

  
    if (parent->value != NULL && !strcmp(parent->value, buffer)) {
        printStack(stack);
        destroyStack(top);
        return NULL;
    } 

    else if (parent->child != NULL) {                
        stack = push(parent->child, stack);        
        return treeSearch(parent->child, buffer, stack);
    }

    else if (parent->brother != NULL) {
        stack = pop(stack);  
        stack = push(parent->brother,stack);
        return treeSearch(parent->brother, buffer, stack);
    }

    else {
        if (parent->parent->brother == NULL) {
            stack = pop(stack);            
            printf("not found\n");
            return NULL;
        }
        else {            
            stack = pop(stack);
            stack = pop(stack);
            stack = push(parent->parent->brother, stack);
            return treeSearch(parent->parent->brother, buffer, stack);
        }
    }    
}   

void treeFind(tree_node_s root, char buffer[]) {    
    tree_node_s current = root->child, previous;
    int i, j=0, found=0, len; 
    char c, directory[MAX_PATH+1];
    len = strlen(buffer);    

    for (i=0; i <= len ; i++) {
        if ((c=buffer[i]) == '/' || c=='\0' || c=='\n') {
            found = 1;
            directory[j] = '\0';  

            if (strcmp(directory, "") && strcmp(directory, "/")) {  
                current = brotherSearch(current, directory); 
                if (current != NULL) {
                    previous = current;
                    current = current->child;
                }
                else {
                    printf("not found\n");
                    return;
                } 
            }

            clear(directory);
            j = 0;
        }
        else if (buffer[i] == ' ' && !found) {
            continue;
        }
        else {
            directory[j++] = buffer[i];
        }
    } 

    
    if (previous->value == NULL) {
        printf("no data\n");
        return;
    }
    else{
        printf("%s\n", previous->value);
        return;
    }
}


/* TODO tree_print */

stack_s treePrint(tree_node_s root, stack_s top) {

    tree_node_s current = root;
    stack_s stack = top;

    
    if (current == NULL) {
        return NULL;
    } 

    if (current->value != NULL) {
      
        printFuncStack(stack);

    }
    

    if (current->child != NULL) {
        stack = push(current->child, stack);

        return treePrint(current->child, stack);
    }

    else {
        if (current->brother != NULL) {
            stack = pop(stack);
            stack = push(current->brother, stack);
            
        
            return treePrint(current->brother, stack);

        }
        else {
            if (current->parent->brother != NULL) {
                stack = pop(stack);
                stack = pop(stack);
                stack = push(current->parent->brother, stack);
                

                return treePrint(current->parent->brother, stack);                    

            }
            
            else {          

                while (current->brother == NULL) {
                    current = current->parent;                    
                    if (!strcmp(current->path, "/")) {
                        
                        destroyStack(stack);
                        return NULL;
                    }
                    stack = pop(stack);
                    
                }
                stack = pop(stack);


                if (current->brother == NULL) {
                    
                    destroyStack(stack);
                    return NULL;
                }
                
                stack = push(current->brother, stack);
                
                return treePrint(current->brother, stack);               

            }
        }
    }
    return NULL;
}

tree_node_s findParent(tree_node_s current, stack_s stack) {
    tree_node_s aux = current;
    while (aux != NULL) {
        if (aux->brother != NULL) {
            return aux;
        }
        else if (!strcmp(aux->path, "/")) {
            return aux;
        }
        aux = aux->parent;
        stack = pop(stack);
    }
    return NULL;
}



/* TODO tree_list */

void listRoot(tree_node_s root) {

    int num_of_nodes, i;
    tree_node_s aux = root->child;
    tree_node_s *sortList;

    num_of_nodes = countNodes(aux);

    sortList = malloc(sizeof(struct tree_node) * num_of_nodes);

    for (i=0; i < num_of_nodes && aux != NULL; i++, aux = aux->brother) {
        sortList[i] = aux;
    }

    quicksort(sortList, 0, num_of_nodes-1);

    for (i=0; i < num_of_nodes; i++) {
        printf("%s\n", sortList[i]->path);        
    }
    free(sortList);
}

void treeList(tree_node_s root, char buffer[]) {

    tree_node_s aux;

    if (strlen(buffer) == 0) {
        listRoot(root);
    }

    else {
        aux = nodeSearch(root, buffer);
        listRoot(aux);
    }


}

tree_node_s nodeSearch(tree_node_s root, char buffer[]) {
    
 

    tree_node_s current = root->child;
    int i, j=0, found=0, len; 
    char c, directory[MAX_PATH+1];
    len = strlen(buffer);  

    for (i=0; i < len ; i++) {
        if ((c=buffer[i]) == '/' || c=='\0' || c=='\n') {
            found = 1;
            directory[j] = '\0';  

            if (strcmp(directory, "") && strcmp(directory, "/")) {  
                current = brotherSearch(current, directory);
                if (current != NULL) {
                    current = current->child;
                }
                else {
                    printf("not found\n");
                    return NULL;
                } 
            }

            clear(directory);
            j = 0;
        }
        else if (buffer[i] == ' ' && !found) {
            continue;
        }
        else {
            directory[j++] = buffer[i];
        }
    } 
    if (strcmp(directory, "") && strcmp(directory, "/")) {  
        current = brotherSearch(current, directory);
    }
    
    return current;
}   


tree_node_s treeDelete(tree_node_s root, char buffer[]) {

    tree_node_s aux, finder, parent;

    if (strlen(buffer) == 0) {
        return NULL;
    }
    else {
        aux = nodeSearch(root, buffer);
        if (!strcmp(aux->parent->child->path, aux->path)) {
            if (aux->brother != NULL)
                aux->parent->child = aux->brother;
            else 
                aux->parent->child = NULL;
        }
        else {
            parent = aux->parent;
            finder = parent->child;
            while (strcmp(finder->brother->path, aux->path)) {
                finder = finder->brother;
            }
            finder->brother = aux->brother;
        }
        treeDestructor(aux);
        return NULL;       

    }
}
