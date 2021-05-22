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
       /* else {
             não! tem pai com irmaos?
            if (node->parent != NULL) {
                sim! dar return ao pai com irmaos (APAGAR AQUI) 
                node->parent->child = NULL;
                aux = node->parent;
                if (node->child == NULL && node->brother == NULL) {
                    printf("[treeDestructor] node will be destroyed! %s\n", node->path);
                    free(node->path);
                    free(node->value);
                    free(node);
                }
                return treeDestructor(aux);
            }          
             nao! procurar o pai com irmaos (APAGAR AQUI) 

        }     */     
    }
    return NULL;
}


void treeAdd(tree_node_s root, char buffer[]) {  
    /* guardar o endereço da root sempre, so mexer no parent*/
    tree_node_s parent = root;
    tree_node_s newchild;

    int i, j=0, found=0, len = strlen(buffer); 
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];

    /*por cada diretorio que leio do terminal*/
    for (i=0; i < len; i++) {
        if ((c = buffer[i]) == '/' || c == ' ' || c == '\0') {
            directory[j] = '\0';           

            if (strcmp(directory,"") && strcmp(directory, "/")) {         
                /*verificar existem filhos*/
                newchild = auxAddTree(parent, directory);
                /*atribuo o pai atual ao campo "parent" do novo filho*/             
                newchild->parent = parent;
                /*agora, o pai(atual) passa a ser o filho que acabei de criar*/
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
    /* quando o dir for NULL, chegámos ao fim, e o value pode ser adicionado ao ultimo child (acabar de ler o value do buffer, aproveitar o valor do i)  */
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
            brother->brother = child;
            return child;
        }
    }
    else {
        /* se nao existirem, tenho de criar uma nova lista de filhos para o atual pai e adicionar o filho criado a primeira posicao*/
        child = newChild(path);
        child->parent = parent;
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
        if (!strcmp(aux->path, path)) {
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
    if (current->value != NULL && !strcmp(current->value, buffer)) {
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
                else if (!strcmp(aux->path, "/")) {
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
    tree_node_s current = root->child, previous;
    int i, j=0, found=0, len; 
    char c, directory[MAX_PATH+1];
    len = strlen(buffer);    

    for (i=0; i <= len ; i++) {
        if ((c=buffer[i]) == '/' || c=='\0' || c=='\n') {
            found = 1;
            directory[j] = '\0';  

            if (strcmp(directory, "") && strcmp(directory, "/")) {  
                /*tenho de ver se o directorio existe, logo vou a procura dele*/
                current = brotherSearch(current, directory);
                /*se existir, passo ao filho como atual*/
                if (current != NULL) {
                    previous = current;
                    current = current->child;
                }
                else {
                    /* se nao existir, lanço erro*/
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

    if (!strcmp(root->path, "/") && root->child==NULL && root->brother==NULL && root->parent==NULL) {
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

                    if (current != NULL && !strcmp(current->path, "/")) {                        
                        
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
        if (aux==NULL) {
            printf("not found\n");
            return;
            
        }
        listRoot(aux);
    }


}

tree_node_s nodeSearch(tree_node_s root, char buffer[]) {
    
    /* fim -> o parent é NULL*/

    tree_node_s current = root->child;
    int i, j=0, found=0, len; 
    char c, directory[MAX_PATH+1];
    len = strlen(buffer);  

    for (i=0; i < len ; i++) {
        if ((c=buffer[i]) == '/' || c=='\0' || c=='\n') {
            found = 1;
            directory[j] = '\0';  

            if (strcmp(directory, "") && strcmp(directory, "/")) {  
                /*tenho de ver se o directorio existe, logo vou a procura dele*/
                current = brotherSearch(current, directory);

                /* se existir, passo ao filho como atual*/
                if (current != NULL && i < len-1) {
                    current = current->child;
                }
                else if(current != NULL && i == len-1) {
                    /* se for o ultimo e houver uma barra */                    
                    return current;
                } 
                else {
                    /*se nao existir, lanço erro*/
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
        /*tenho de ver se o directorio existe, logo vou a procura dele*/
        current = brotherSearch(current, directory);
    }
    
    return current;
}   


tree_node_s treeDelete(tree_node_s root, char buffer[]) {

    tree_node_s aux, finder, parent;

    if (strlen(buffer) == 0) {
        treeCompletlyDestructor(root);
        return NULL;
    }
    else {
        aux = nodeSearch(root, buffer);  

        if (aux==NULL) {
            printf("not found\n");
            return NULL;
        }      

        /*se for o primeiro filho dos pais, substituir pelo irmao (se houver) */

        /*se tiver irmaos e nao for o filho direto, procurar o irmao anterior*/
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
        treePartialDestructor(aux);
        return NULL;       

    }
}
