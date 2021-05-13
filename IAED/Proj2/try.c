#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "private.h"
#include "public.h"
#define MAX_PATH

list_node_s lastsList(tree_node_s root) {
    list_node_s lstnode = listConstructor();
    tree_node_s aux = root;
    // procurar o ultimo filho de cada ramo que ja nao possua filhos
    if (aux==NULL) {
        return NULL;
    }

    //quando ja nao há filhos, passa a procura recursiva ao irmao

    // encontrei o ultimo filho de um ramo
    if (aux->child==NULL && aux!=NULL) {
        lstnode->current = aux;
        lstnode = lstnode->next;
    }

    // procuro filhos

    if (aux->child != NULL) {
        aux = aux->child;
        return lastsList(aux);
    }




    // quando encontrado, adicionar ao lstnode








    return lstnode;
}

list_node_s listConstructor(){
    list_node_s newnode = (list_node_s) malloc(sizeof(struct list_node));
    newnode->current = NULL;
    newnode->next = NULL;
    return newnode;
}



int main() {

    // len 11

    char *teste;
    char *pila;
    teste = (char*) malloc(sizeof(char)*12);

    strcpy(teste, "ola bom dia");

    pila = teste;

    free(pila);

    return 0;
}