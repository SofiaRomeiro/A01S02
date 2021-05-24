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
    new_tree->path[0] = '\0';
    strcpy(new_tree->path, ROOT);
    new_tree->value = NULL;
    new_tree->brother = NULL;
    new_tree->child = NULL;
    new_tree->num_of_children = 0;
    new_tree->parent = NULL;
    return new_tree;
}

tree_node_s newTreeNode() {
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node));
    new_node->value = NULL;
    new_node->path = NULL;
    new_node->child = NULL;
    new_node->brother = NULL;
    new_node->num_of_children = 0;
    new_node->parent = NULL;
    return new_node;
}

tree_node_s treeCompletlyDestructor(tree_node_s node) {
    tree_node_s aux;

    /* se ja é nulo , ver se todos os componentes sao nulos*/

    if (node == NULL) {
        return NULL;
    }

    /* se nao tem filhos nem irmao, pode apagar */
    /*if (node->child == NULL && node->brother == NULL) {
        free(node->path);
        free(node->value);
        free(node);
    }*/

    /* tem filhos ? */
    if (node->child != NULL) {
        /* sim! passa aos filhos */
        return treeCompletlyDestructor(node->child);

    }
    else {
        /* não! tem irmaos? */
        if (node->brother != NULL) {
            /* sim! ligar o pai ao irmao, e apagar o respetivo node (APAGA AQUI) */
            node->parent->child = node->brother;
            aux = node->brother;
            node->brother=NULL;
            node->child=NULL;
            if (node->child == NULL && node->brother == NULL) {
                free(node->path);
                free(node->value);
                free(node);
            }
            return treeCompletlyDestructor(aux);
        } 
        else {
            /* não! tem pai com irmaos?*/
            if (node->parent != NULL) {
                /*sim! dar return ao pai com irmaos (APAGAR AQUI)*/ 
                node->parent->child = NULL;
                aux = node->parent;
                if (node->child == NULL && node->brother == NULL) {
                    free(node->path);
                    free(node->value);
                    free(node);
                }
                return treeCompletlyDestructor(aux);
            }          
             /*nao! procurar o pai com irmaos (APAGAR AQUI) */

        }         
    }
    return NULL;
}


tree_node_s treePartialDestructor(tree_node_s node) {
    tree_node_s aux;


    /* se ja é nulo , ver se todos os componentes sao nulos*/

    if (node == NULL) {
        return NULL;
    }

    /* se nao tem filhos nem irmao, pode apagar */
    /*if (node->child == NULL && node->brother == NULL) {
        free(node->path);
        free(node->value);
        free(node);
    }*/

    /* tem filhos ? */
    if (node->child != NULL) {
        /* sim! passa aos filhos */
        return treePartialDestructor(node->child);

    }
    else {
        /* não! tem irmaos? */
        if (node->brother != NULL) {
            /* sim! ligar o pai ao irmao, e apagar o respetivo node (APAGA AQUI) */
            node->parent->child = node->brother;
            aux = node->brother;
            if (node->child == NULL && node->brother == NULL) {
                free(node->path);
                free(node->value);
                free(node);
            }
            return treePartialDestructor(aux);
        }     
    }
    return NULL;
}


void treeAdd(tree_node_s root, char buffer[]) {  
    /* guardar o endereço da root sempre, so mexer no parent*/
    tree_node_s parent = root;
    tree_node_s current=NULL;
    char *path_p=NULL, *directory=NULL;
    int size; 
    char path[MAX_PATH+1], value[MAX_PATH+1];

    path[0] = '\0';
    value[0] = '\0';

  
    /* formação do path e do value */
    path_p = strtok(buffer, " \t");
    strcat(path, path_p);
    path_p = strtok(NULL, " \t");

    while (path_p != NULL) {  
        strcat(value, path_p);
        strcat(value, " ");      
        path_p = strtok(NULL, " \t");
    }
    size = strlen(value);
    value[size-1] = '\0';

    /*inserção */

    directory = strtok(path, "/");
    current = auxAddTree(parent, directory);
    current->parent = parent;
    parent = current;


    while (directory != NULL) {

        directory = strtok(NULL, "/");
        if (directory==NULL) break;
        current = auxAddTree(parent, directory);
        current->parent = parent;
        parent = current;
    }

    current->value = (char *) malloc(sizeof(char)*(size+1)); 
    current->value[0] = '\0'; 
    strcpy(current->value, value);

    clear(value);
    clear(path);  
}

tree_node_s auxAddTree(tree_node_s parent, char path[]) {

    /*o parent do input sera colocado no campo "parent" do novo filho*/

    /* o filho que vou criar*/
    tree_node_s child;
    /* o irmao, caso nao exista ainda o path, que será o antecessor do novo node a criar com o path*/
    tree_node_s brother;

    /*verificar existem filhos*/

    if (parent->child != NULL) {
        /*existem, logo tenho de saber se o path a criar ja existe nos filhos*/
        
        brother = brotherSearch(parent->child, path); /*procurar o sitio onde esta o path(filho), se nao existir return NULL*/

        if (brother != NULL) {
            /* ja existe o filho, logo será o meu novo pai*/
            return brother;
        }
        else {
        /* nao existe ainda o path a criar, logo vou procurar onde o inserir*/  
            brother = findBrotherNode(parent->child);
            child = newChild(path); /*novo irmao do brother que retornei*/
            child->parent = parent;
            parent->num_of_children += 1;
            brother->brother = child;
            return child;
        }
    }
    else {
        /* se nao existirem, tenho de criar uma nova lista de filhos para o atual pai e adicionar o filho criado a primeira posicao*/
        child = newChild(path);
        child->parent = parent;
        parent->num_of_children += 1;
        parent->child = child;
        return child;
    }

    /*agora, o pai(atual) passa a ser o filho que acabei de criar (return no pai atual)*/
}

tree_node_s findBrotherNode(tree_node_s current){
    /* devolve o irmao, de forma a inserir o novo irmao na posicao next*/
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
    newchild->path[0] = '\0';
    strcpy(newchild->path, path);
    newchild->child = NULL;
    newchild->brother = NULL;
    newchild->parent = NULL;
    newchild->value = NULL;

    return newchild;
}

tree_node_s brotherSearch(tree_node_s child, char path[]){
    /*procura a ver se existe algum no com o path igual ao do path(input)*/
    tree_node_s aux = child;
    /* procura a ver se existe algum node(child) com o path que quero criar*/
    while (aux != NULL) {
        if (!hashing(aux->path, path)) {
            return aux;
        }
        aux = aux->brother;
    }
    return NULL;
}


tree_node_s treeSearch(tree_node_s root, char buffer[], stack_s top) {
    tree_node_s current = root, aux;
    stack_s stack = top;

    /* fim -> o parent é NULL */

    if (current == NULL) { 
        printf("not found\n");       
        return NULL;
    }


    /*encontrou o valor, PARA tudo! */
    if (current->value != NULL && !hashing(current->value, buffer)) {
        stack = push(current, stack);        
        printStack(stack);
        destroyStack(stack);
        return NULL;
    } 

    /* tem filhos ? */
        /* sim! passa para o proximo filho*/
    else if (current->child != NULL) {              
        stack = push(current->child, stack);        
        return treeSearch(current->child, buffer, stack);
    }

    /* não! passa para o irmao*/
    else if (current->brother != NULL) {
        stack = pop(stack);          
        stack = push(current->brother,stack);
        return treeSearch(current->brother, buffer, stack);
    }

    /*tem irmao e nao tem filhos? */   
    else {
        /* nao! procura um parent que tenha irmaos*/
        if (current->parent!= NULL && current->parent->brother == NULL) {
            /*stack = pop(stack);*/         
            
            /*current = findParent(current, stack);*/

            /* ---------------------------------------------*/
            aux = current;
            /* tenho de procurar um pai que tenha irmaos*/
            while (aux->parent != NULL) {
                /*encontrou um parent com irmao -> devolve esse irmao*/
                if (aux->brother != NULL) {
                    stack = pop(stack);                    
                    stack = push(aux->brother, stack);
                    return treeSearch(aux->brother, buffer, stack);
                }
                /* chegou à root*/
                else if (!hashing(aux->path, "/")) {
                    stack = pop(stack);
                    return treeSearch(aux, buffer, stack);
                } 
                
                aux = aux->parent;
                stack = pop(stack);
            }
        }
        else if (current->parent== NULL) {
            printf("not found\n");
            return NULL;
        }
            
        else {        
            stack = pop(stack);
            stack = pop(stack);
            stack = push(current->parent->brother, stack);
            return treeSearch(current->parent->brother, buffer, stack);
        }
    }   
    printf("not found\n");
    return NULL; 
}   

void treeFind(tree_node_s root, char buffer[]) {    
   tree_node_s current = root;
    char *array;  

    array = strtok(buffer, "/"); 
    current = current->child;
    current = brotherSearch(current, array);


    while (array != NULL) {
        
        /* se nao existir, lanço erro*/
        if (current == NULL) {
            printf("not found\n");
            return;
        }  
        array = strtok(NULL, "/"); 
        if (array==NULL) break; 
        current = current->child;
        current = brotherSearch(current, array);    
        
    }
    
    if (current->value == NULL) {
        printf("no data\n");
        return;
    }
    else{
        printf("%s\n", current->value);
        return;
    }
}


/* TODO tree_print */

stack_s treePrint(tree_node_s root, stack_s top) {

    tree_node_s current = root;
    stack_s stack = top;

    if (!hashing(root->path, "/") && root->child==NULL && root->brother==NULL && root->parent==NULL) {
        return NULL;
    }
    
    /*current é nulo?*/
    if (current == NULL) {
        /* sim !! -> acaba o ciclo;*/
        return NULL;
    } 
        /* nao!! -> continua*/

    /* current tem valor?*/
    if (current->value != NULL) {
        /*sim !!
            print da stack
            continua*/
            
        printFuncStack(stack);
        /*nao !!
            passa a frente*/
    }
    
    /* current tem filhos?*/
    

    if (current->child != NULL) {
        /*sim !!
            o que acontece à stack? coloca o proximo filho na stack*/
        stack = push(current->child, stack);
        
        /*passa ao filho*/
        return treePrint(current->child, stack);
    }
   

    else {
        /*nao !!
       
        / tem irmaos ?*/
        if (current->brother != NULL) {
            /*sim !!
                o que acontece à stack? tiro o node atual e coloco o irmao na stack*/
            stack = pop(stack);
            stack = push(current->brother, stack);
            
            /*passa para o irmao*/
            return treePrint(current->brother, stack);

        }
        else {
            /*nao !!
                o pai tem irmaos ?*/
           

            if (current->parent != NULL && current->parent->brother != NULL) {
                 
                /*sim!! 
                    o que acontece à stack? tira o atual e o pai do atual e coloca lá o irmao do pai do atual*/
                stack = pop(stack);
                stack = pop(stack);
                stack = push(current->parent->brother, stack);
                
                /*passa para o irmao do pai*/
                return treePrint(current->parent->brother, stack);                    

            }

             
            
            else {
            /*nao !!
                procurar o proximo pai que tenha irmaos*/            
                 
                while (current->brother == NULL) {  
                    
                    current = current->parent; 

                    if (current != NULL && !hashing(current->path, "/")) {                        
                        
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
    /* tenho de procurar um pai que tenha irmaos*/
    while (aux->parent != NULL) {
        /*encontrou um parent com irmao -> devolve esse irmao*/
        if (aux->brother != NULL) {
            /*stack = push(aux->brother, stack);*/
            return aux->brother;
        }
        /*chegou à root*/
        else if (!hashing(aux->path, "/")) {
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

    

    num_of_nodes = root->num_of_children;

    sortList = malloc(sizeof(struct tree_node) * num_of_nodes);



    for (i=0; i < num_of_nodes && aux != NULL; i++, aux = aux->brother) {
        sortList[i] = NULL;
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
        if (aux==NULL) {
            printf("not found\n");
            return;
            
        }
        listRoot(aux);
    }


}

tree_node_s nodeSearch(tree_node_s root, char buffer[]) {
    
    /* fim -> o parent é NULL*/

    tree_node_s current = root; 
    char *array;   
 
    array = strtok(buffer, "/");
    current = current->child;
    current = brotherSearch(current, array);

     while (array != NULL) {
        if (current==NULL) {
            return current;
        }
        array = strtok(NULL, "/");
        if (array == NULL) break;
        current = current->child;        
        current = brotherSearch(current, array);      
    }
    return current;
    
}   


tree_node_s treeDelete(tree_node_s root, char buffer[]) {

    tree_node_s aux=root, finder, parent;
    char *array;

    if (strlen(buffer) == 0) {
        treeCompletlyDestructor(root);
        return NULL;
    }
    else {
        
        /*aux = nodeSearch(root, buffer);  */

        array = strtok(buffer, "/"); 

        while (array != NULL) {

            aux = aux->child;  
            aux = brotherSearch(aux, array);           
        
            if (aux == NULL) {
                printf("not found\n");
                return NULL;
            }   
            if (aux->child == NULL) {
                break;
            }     
            array = strtok(NULL, "/"); 
            
        }

        if (aux != NULL && !hashing(aux->path, ROOT)) {
            treeCompletlyDestructor(root);
            return NULL;
        }
   

       /* if (aux==NULL) {
            printf("not found\n");
            return NULL;
        }   */

        /*se for o primeiro filho dos pais, substituir pelo irmao (se houver) */

        /*se tiver irmaos e nao for o filho direto, procurar o irmao anterior*/
        if (aux != NULL && aux->parent != NULL && aux->parent->child != NULL && !hashing(aux->parent->child->path, aux->path)) {
            if (aux->brother != NULL) {
                aux->parent->child = aux->brother;
                aux->parent->num_of_children -= 1;
                aux->brother = NULL;
            }
            else {
                aux->parent->num_of_children -= 1;
                aux->parent->child = NULL;
            }
        }
        else {
            parent = aux->parent;
            finder = parent->child;
            while (finder->brother != NULL && aux != NULL && hashing(finder->brother->path, aux->path)) {
                finder = finder->brother;
            }
            finder->brother = aux->brother;
            parent->num_of_children -= 1;
            aux->brother = NULL;
        }
        aux->parent = NULL;      
        treePartialDestructor(aux);
        return NULL;       

    }
}