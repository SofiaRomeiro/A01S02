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
void treeDestructor(tree_node_s node) {

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



/* TODO tree_print */

void treePrint(tree_node_s root) {

}
/* TODO tree_delete */
/* TODO tree_search */
void Printer(tree_node_s node) {
    printf("[Printer] value: %s\n", node->value);
}

tree_node_s treeSearch(tree_node_s root, char buffer[]) {
    tree_node_s aux = root;

    if (aux == NULL)
        return NULL;
    if (aux->value != NULL && !strcmp(aux->value, buffer)) {
        Printer(aux);  
        return NULL;
    } 
    else if (aux->child != NULL) {
        return treeSearch(aux->child, buffer);
    }
    else if (aux->brother != NULL) {
        return treeSearch(aux->brother, buffer);
    }
    else {
        if (aux->parent->brother == NULL)
            return NULL;
        else 
            return treeSearch(aux->parent->brother, buffer);
    }


    // fim -> o parent é NULL    
    // encontrou o valor, PARA tudo!   

    // tem filhos ? 
        // sim! passa para o proximo filho
        // não! passa para o irmao
   
    // tem irmao e nao tem filhos?    
        // sim! passa para o irmao 
        // nao! volta para o parent e passa para o proximo irmao do parent     
}    

tree_node_s searchBinary(tree_node_s root, char buffer[]) {
    tree_node_s aux=root;

    // criar lista com todos os parents que antecedem o ultimo filho (um genero de list node)

    // se i input for nulo, devolvo null    

    // (estar sempre a ver se e o argumento que eu quero)

    // se nao for null, iniciar a procura pelo ultimo filho        

    // se nao encontrar
    
    // PROBLEMA !!! QUANDO O VALUE A PROCURAR ESTA NUM RAMO SUPERIOR AQUELE PARA O QUAL O ALGORITMO PASSOU

    
}

// TODO treeFind
void treeFind(tree_node_s root, char buffer[]) {    
    tree_node_s current = root->child, previous;
    int i, j=0, found=0, len; 
    char c, directory[MAX_PATH+1],value[MAX_PATH+1];

    // ERROS :
        // not found
        // no data

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
/* TODO tree_list */