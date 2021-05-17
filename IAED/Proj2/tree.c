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

// TODO treeDestructor
tree_node_s treeDestructor(tree_node_s node) {

}



void treeAdd(tree_node_s root, char buffer[]) {  
    /* guardar o endereço da root sempre, so mexer no parent*/
    tree_node_s parent = root;
    tree_node_s newchild /*= newTreeNode()*/;

    int i, j=0, found=0, len = strlen(buffer); 
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];

    //por cada diretorio que leio do terminal    
    for (i=0; i < len; i++) {
        if ((c = buffer[i]) == '/' || c == ' ' || c == '\0') {
            directory[j] = '\0';           

            if (strcmp(directory,"") && strcmp(directory, "/")) {         
                //verificar existem filhos
                newchild = auxAddTree(parent, directory);
                // atribuo o pai atual ao campo "parent" do novo filho                
                newchild->parent = parent;
                 // agora, o pai(atual) passa a ser o filho que acabei de criar
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
    // quando o dir for NULL, chegámos ao fim, e o value pode ser adicionado ao ultimo child (acabar de ler o value do buffer, aproveitar o valor do i)  
    for (; i < len; i++) {
        if (buffer[i] == ' ' && !found) { 
        }  
        else {
            found = 1;
            value[j++] = buffer[i];         
        }
    }
    value[j] = '\0';

    //if (newchild->value != NULL) {
    //    free(newchild->value);
    //}
    
    newchild->value = (char *) malloc(sizeof(char)*(strlen(value)+1));
    strcpy(newchild->value, value);

    clear(value);
    clear(directory);   
}

tree_node_s auxAddTree(tree_node_s parent, char path[]) {

    //o parent do input sera colocado no campo "parent" do novo filho

    // o filho que vou criar
    tree_node_s child;
    // o irmao, caso nao exista ainda o path, que será o antecessor do novo node a criar com o path
    tree_node_s brother;

    //verificar existem filhos

    if (parent->child != NULL) {
        // existem, logo tenho de saber se o path a criar ja existe nos filhos
        
        brother = brotherSearch(parent->child, path); //procurar o sitio onde esta o path(filho), se nao existir return NULL

        if (brother != NULL) {
            // ja existe o filho, logo será o meu novo pai
            return brother;
        }
        else {
        // nao existe ainda o path a criar, logo vou procurar onde o inserir        
            brother = findBrotherNode(parent->child, path);
            child = newChild(path); //novo irmao do brother que retornei
            child->parent = parent;
            brother->brother = child;
            return child;
        }
    }
    else {
        // se nao existirem, tenho de criar uma nova lista de filhos para o atual pai e adicionar o filho criado a primeira posicao
        child = newChild(path);
        child->parent = parent;
        parent->child = child;
        return child;
    }

    // agora, o pai(atual) passa a ser o filho que acabei de criar (return no pai atual)
}

tree_node_s findBrotherNode(tree_node_s current, char path[]){
    // devolve o irmao, de forma a inserir o novo irmao na posicao next
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
    //procura a ver se existe algum no com o path igual ao do path(input)
    tree_node_s aux = child;
    // procura a ver se existe algum node(child) com o path que quero criar
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
    // fim -> o parent é NULL 

    if (parent == NULL) {        
        return NULL;
    }

    // encontrou o valor, PARA tudo! 
    if (parent->value != NULL && !strcmp(parent->value, buffer)) {
        printStack(stack);
        destroyStack(top);
        return NULL;
    } 

    // tem filhos ? 
        // sim! passa para o proximo filho
    else if (parent->child != NULL) {                
        stack = push(parent->child, stack);        
        return treeSearch(parent->child, buffer, stack);
    }

    // não! passa para o irmao
    else if (parent->brother != NULL) {
        stack = pop(stack);  
        stack = push(parent->brother,stack);
        return treeSearch(parent->brother, buffer, stack);
    }

     // tem irmao e nao tem filhos?      
    else {
        // nao! volta para o parent e passa para o proximo irmao do parent 
        if (parent->parent->brother == NULL) {
            stack = pop(stack);            
            printf("not found\n");
            return NULL;
        }
        // sim! passa para o irmao 
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
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];


    read(buffer);
    len = strlen(buffer);    

    for (i=0; i <= len ; i++) {
        if ((c=buffer[i]) == '/' || c=='\0') {
            found = 1;
            directory[j] = '\0';  

            if (strcmp(directory, "") && strcmp(directory, "/")) {  
                //tenho de ver se o directorio existe, logo vou a procura dele
                current = brotherSearch(current, directory); // MUDEI AQUI !!!
                // se existir, passo ao filho como atual
                if (current != NULL) {
                    previous = current;
                    current = current->child;
                }
                else {
                    // se nao existir, lanço erro
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

    //current é nulo?
    if (current == NULL) {
        destroyStack(top);
        // sim !! -> acaba o ciclo
        return NULL;
    }    

        // nao!! -> continua

    // current tem valor?
    if (current->value != NULL) {
        //sim !!
            // print da stack
            // continua
        printFuncStack(stack);        

        //nao !!
            // passa a frente
    }
    
    // current tem filhos?

    if (current->child != NULL) {

        //sim !!
        // o que acontece à stack? coloca o proximo filho na stack
        stack = push(current->child, stack);
        //passa ao filho
        return treePrint(current->child, stack);
    }

    else {
        //nao !!
                  
        // tem irmaos ?
        if (current->brother != NULL) {
            //sim !!
            // o que acontece à stack? tiro o node atual e coloco o irmao na stack
            stack = pop(stack);
            stack = push(current->brother, stack);
            //passa para o irmao
            return treePrint(current->brother, stack);

        }
        else {
            //nao !!
            // o pai tem irmaos ?

            if (current->parent->brother != NULL) {
                //sim!! 
                // o que acontece à stack? tira o atual e o pai do atual e coloca lá o irmao do pai do atual
                stack = pop(stack);
                stack = pop(stack);
                stack = push(current->parent->brother, stack);
                // passa para o irmao do pai
                return treePrint(current->parent->brother, stack);                    

            }
            
            else {
            //nao !!
                // o que acontece à stack? destruir !!!!!!!!!!
                // acaba o ciclo
                destroyStack(top);
                return NULL;

            }

                

                
                   

        }

                
 
    }
    

       


    return NULL;
}


/* TODO tree_list */

/* TODO tree_delete */