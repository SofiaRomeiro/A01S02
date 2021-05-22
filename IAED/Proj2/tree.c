#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"


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

tree_node_s newTreeNode(char path[]){
    tree_node_s new_node = (tree_node_s) malloc(sizeof(struct tree_node)); 
    new_node->child = NULL;
    new_node->brother = NULL;
    new_node->path = (char *) malloc(sizeof(char) * (strlen(path)+1));
    strcpy(new_node->path, path);
    new_node->value = NULL;   
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
    tree_node_s current;
    char *path_p, *directory;
    int size; 
    char path[MAX_PATH+1], value[MAX_PATH+1];


    /* formação do path e do value */
    path_p = strtok(buffer, " ");
    strcat(path, path_p);
    path_p = strtok(NULL, " ");

    while (path_p != NULL) {  
        strcat(value, path_p);
        strcat(value, " ");      
        path_p = strtok(NULL, " ");
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
    strcpy(current->value, value);

    clear(value);
    clear(path); 
}

tree_node_s auxAddTree(tree_node_s parent, char path[]) {

    tree_node_s child;
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
        /* nao existe ainda o path a criar, mas ja existem irmaos, logo vou procurar onde posso inserir*/  
            brother = brotherSearch(parent->child, NULL);
            child = newTreeNode(path);
            child->parent = parent;
            brother->brother = child;  /*novo irmao do brother que retornei*/
            return child;
        }
    }
    else {
        /* se nao existirem, tenho de criar uma nova lista de filhos para o atual pai e adicionar o filho criado a primeira posicao*/
        child = newTreeNode(path);
        child->parent = parent;
        parent->child = child;
        return child;
    }

    /*agora, o pai(atual) passa a ser o filho que acabei de criar (return no pai atual)*/
}

tree_node_s brotherSearch(tree_node_s current, char path[]) {
    /*procura a ver se existe algum no com o path igual ao do path(input)*/
    tree_node_s aux = current;
    /* procura a ver se existe algum node(child) com o path que quero criar*/
    /* se for nulo, apenas quero saber onde vou inserir o meu irmao */


    if (path == NULL) {
        while (aux->brother != NULL) {
            aux = aux->brother;
        }
        return aux;
    }

    else {
        while (aux != NULL) {
            if (strcompare(aux->path, path)) {
                return aux;
            }
            aux = aux->brother;
        }
        return NULL;
    }    
   
}

tree_node_s treeSearch2(tree_node_s root, list_ext_s extremes, list_node_s head, char buffer[]) {
    tree_node_s current = root;
    list_node_s list = head;

    /* se nao for igual à root*/
    if (!strcompare(root->path, "/") && root->child==NULL && root->brother==NULL && root->parent==NULL) {
        return NULL;
    }
    
    /*current é nulo?*/
    if (current == NULL) {
        /* sim !! -> acaba o ciclo;*/
        return NULL;
    } 
        /* nao!! -> continua*/

    /* current tem valor?*/
    if (current->value != NULL && strcompare(current->value, buffer)) {
        /*sim !!
            print da stack
            continua*/
         
        printSearch(extremes);
        destroyList(extremes);
        return NULL;
        /*nao !!
            passa a frente*/
    }
    
    /* current tem filhos?*/
    

    if (current->child != NULL) {
        /*sim !!
            o que acontece à stack? coloca o proximo filho na stack*/
        list = insertEnd(extremes, list, current->child);
        
        /*passa ao filho*/
        return treeSearch2(current->child, extremes, list, buffer);
    }
   

    else {
        /*nao !!
       
        / tem irmaos ?*/
        if (current->brother != NULL) {
            /*sim !!
                o que acontece à stack? tiro o node atual e coloco o irmao na stack*/
            list = deleteEnd(extremes, list);
            list = insertEnd(extremes, list, current->brother);
            
            /*passa para o irmao*/
            return treeSearch2(current->brother, extremes, list, buffer);

        }
        else {
            /*nao !!
                o pai tem irmaos ?*/
           

            if (current->parent != NULL && current->parent->brother != NULL && current != NULL) {
                 
                /*sim!! 
                    o que acontece à stack? tira o atual e o pai do atual e coloca lá o irmao do pai do atual*/
                list = deleteEnd(extremes, list);                
                list = deleteEnd(extremes, list);
                list = insertEnd(extremes, list, current->parent->brother);
                
                /*passa para o irmao do pai*/
                return treeSearch2(current->parent->brother, extremes, list, buffer);                  

            }             
            
            else {
            /*nao !!
                procurar o proximo pai que tenha irmaos*/            
                 
                while (current!= NULL && current->brother == NULL) {  
                    
                    current = current->parent; 

                    /* se for igual à root*/
                    if (current != NULL && strcompare(current->path, "/")) {                       
                        destroyList(extremes);
                        return NULL;
                    }   

                    list = deleteEnd(extremes, list);                    
                    
                }               
                list = deleteEnd(extremes, list);
                
                if (current != NULL && current->brother == NULL) {
                    destroyList(extremes);
                    return NULL;
                }
                list= insertEnd(extremes, list, current->brother);                
                return treeSearch2(current->brother, extremes, list, buffer);               

            }
        }
    }
    return NULL;
}



tree_node_s treeSearch(tree_node_s root, list_ext_s extremes, list_node_s head, char buffer[]) {
    tree_node_s current = root, aux; 

    /* fim -> o parent é NULL */


    if (current == NULL) { 
        printf("not found\n");       
        return NULL;
    }

    /*encontrou o valor, PARA tudo! */
    if (current->value != NULL && strcompare(current->value, buffer)) {
        head = insertEnd(extremes, head, current);
        printSearch(extremes);
        destroyList(extremes);
        return NULL;
    } 

    /* tem filhos ? */
        /* sim! passa para o proximo filho*/
    else if (current->child != NULL) {   
        head = insertEnd(extremes, head, current->child);       
        return treeSearch(current->child, extremes, head, buffer);
    }

    /* não! passa para o irmao*/
    else if (current->brother != NULL) {
        
        head = deleteEnd(extremes, head);
        head= insertEnd(extremes, head, current->brother);  
        return treeSearch(current->brother, extremes, head, buffer);
    }

    /* nao tem irmao e nao tem filhos? */   
    else {
        if (current->parent == NULL) {
            printf("not found\n");
            return NULL;
        }
         /* nao! procura um parent que tenha irmaos pois o parent direto nao tem irmaos*/
        else if (current->parent != NULL && current->parent->brother == NULL) {
  
            aux = current;
            /* tenho de procurar um pai que tenha irmaos*/
            while (aux->parent != NULL) {
                /*encontrou um parent com irmao -> devolve esse irmao*/
                if (aux->brother != NULL) {
                    head= deleteEnd(extremes, head);
                    head= insertEnd(extremes, head, aux->brother);  
                    return treeSearch(aux->brother, extremes, head, buffer);
                }
                /* chegou à root*/
                else if (strcompare(aux->path, ROOT)) {
                    head= deleteEnd(extremes,head);
                    return treeSearch(aux, extremes, head, buffer);
                } 
                
                aux = aux->parent; 
                head= deleteEnd(extremes, head);             
            }
        }
        
        /* o parent tem irmaos, logo passa para o parent */   
        else {        
            head= deleteEnd(extremes, head);
            head= deleteEnd(extremes, head);
            head= insertEnd(extremes,head, current->parent->brother);
            return treeSearch(current->parent->brother, extremes, head, buffer);
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

list_ext_s treePrint(tree_node_s root, list_ext_s extremes, list_node_s head, char buffer[]) {

    tree_node_s current = root;
    list_node_s list = head;

    /* se nao for igual à root*/
    if (!strcompare(root->path, "/") && root->child==NULL && root->brother==NULL && root->parent==NULL) {
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
         
        printList(extremes);
        /*nao !!
            passa a frente*/
    }
    
    /* current tem filhos?*/
    

    if (current->child != NULL) {
        /*sim !!
            o que acontece à stack? coloca o proximo filho na stack*/
        list = insertEnd(extremes, list, current->child);
        
        /*passa ao filho*/
        return treePrint(current->child, extremes, list, buffer);
    }
   

    else {
        /*nao !!
       
        / tem irmaos ?*/
        if (current->brother != NULL) {
            /*sim !!
                o que acontece à stack? tiro o node atual e coloco o irmao na stack*/
            list = deleteEnd(extremes, list);
            list = insertEnd(extremes, list, current->brother);
            
            /*passa para o irmao*/
            return treePrint(current->brother, extremes, list, buffer);

        }
        else {
            /*nao !!
                o pai tem irmaos ?*/
           

            if (current->parent != NULL && current->parent->brother != NULL) {
                 
                /*sim!! 
                    o que acontece à stack? tira o atual e o pai do atual e coloca lá o irmao do pai do atual*/
                list = deleteEnd(extremes, list);                
                list = deleteEnd(extremes, list);
                list = insertEnd(extremes, list, current->parent->brother);
                
                /*passa para o irmao do pai*/
                return treePrint(current->parent->brother, extremes, list, buffer);                  

            }

             
            
            else {
            /*nao !!
                procurar o proximo pai que tenha irmaos*/            
                 
                while (current->brother == NULL) {  
                    
                    current = current->parent; 

                    /* se for igual à root*/
                    if (current != NULL && strcompare(current->path, "/")) {                        
                        
                        destroyList(extremes);
                        return NULL;
                    }                      
                    list = deleteEnd(extremes, list);                    
                    
                }               
                list = deleteEnd(extremes, list);   

                if (current->brother == NULL) {
                    destroyList(extremes);
                    return NULL;
                }

                list= insertEnd(extremes, list, current->brother);                
                return treePrint(current->brother, extremes, list, buffer);               

            }
        }
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

    tree_node_s current=root;
    char *array;

    if (root->child == NULL) {
        printf("not found\n");
        return;
    }

    if (strlen(buffer) == 0) {
        listRoot(root); 
    }
    else {

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

        listRoot(current);
    }
     

    
}
/*
tree_node_s nodeSearch(tree_node_s root, char directory[]) {

    tree_node_s previous=root, current = root->child; 
    char *array, *previous_array;   
 
    array = strtok(directory, "/");
    current = brotherSearch(current, array);
    current = current->child;

    while (array != NULL) {
        
        current = brotherSearch(current, array);        
            if (current != NULL) {
                previous = current;
                current = current->child;
            }
        previous_array = array;
        array = strtok(NULL, "/");
    }

    if (current!= NULL && strcompare(previous_array, current->path)) {
        return current;
    }
    else {
        return previous;
    }
    return NULL;
}*/

tree_node_s treeDelete(tree_node_s root, char buffer[]) {

    tree_node_s to_delete=root, parent, previous_brother;
    char *array; 

    if (strlen(buffer) == 0) {
        treeCompletlyDestructor(root);
        return NULL;
    } 

 
    array = strtok(buffer, "/");   

    while (array != NULL) {

        to_delete = to_delete->child;  
        to_delete = brotherSearch(to_delete, array);           
     
        if (to_delete == NULL) {
            return NULL;
        }   
        if (to_delete->child == NULL) {
            break;
        }     
        array = strtok(NULL, "/"); 
        
    }

    if (strcompare(to_delete->path, ROOT)) {
        treeCompletlyDestructor(root);
        return NULL;
    }

    else {
        /*se for o primeiro filho dos pais, substituir pelo irmao (se houver) */
        
        if (strcompare(to_delete->parent->child->path, to_delete->path)) {
            if (to_delete->brother != NULL) {
                to_delete->parent->child = to_delete->brother;
                to_delete->brother = NULL;
            }
            else {
                to_delete->parent->child = NULL;
            }
            to_delete->parent = NULL;            
       
        }
        else {
            /* se nao for o primeiro filho */
            /*se tiver irmaos e nao for o filho direto, procurar o irmao anterior*/
            parent = to_delete->parent;
            /* a pesquisa começa no primeiro filho direto do pai */
            previous_brother = parent->child;
            to_delete->parent = NULL;
            /* enquanto forem diferentes */
            while (!strcompare(previous_brother->brother->path, to_delete->path)) {
                previous_brother = previous_brother->brother;
            }
            previous_brother->brother = to_delete->brother;
            to_delete->brother = NULL;
        }
              
    }
    treePartialDestructor(to_delete);
    return NULL;
}
